#include "sim2d/sim.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace sim2d {
namespace {
constexpr double kMinRange = 1e-9;

double squared_distance(Vec2 a, Vec2 b) {
  const double dx = a.x - b.x;
  const double dy = a.y - b.y;
  return dx * dx + dy * dy;
}
} // namespace

double normalize_angle(double angle) {
  angle = std::fmod(angle + kPi, 2.0 * kPi);
  if (angle < 0.0)
    angle += 2.0 * kPi;
  return angle - kPi;
}

Simulator2D::Simulator2D(WorldConfig config) { reset(std::move(config)); }

void Simulator2D::reset() { reset(config_); }

void Simulator2D::reset(WorldConfig config) {
  validate_config(config);
  config_ = std::move(config);
  pose_ = config_.initial_pose;
  pose_.theta = normalize_angle(pose_.theta);
  landmarks_ = config_.landmarks;
  time_ = 0.0;
  step_index_ = 0;
  next_landmark_id_ = 0;
  assign_missing_landmark_ids();
  seed_rng();
}

StepResult Simulator2D::step(Control command, bool collect_observations) {
  const Control odometry = sample_odometry(command);
  pose_ = integrate(pose_, command);
  ++step_index_;
  time_ += config_.time_step;

  StepResult result;
  result.step_index = step_index_;
  result.time = time_;
  result.true_pose = pose_;
  result.command = command;
  result.odometry = odometry;
  if (collect_observations)
    result.observations = sense();
  return result;
}

std::vector<Observation> Simulator2D::sense() {
  std::vector<Observation> observations;
  observations.reserve(landmarks_.size());

  const Vec2 robot{pose_.x, pose_.y};
  for (const Landmark &landmark : landmarks_) {
    const double dx = landmark.position.x - robot.x;
    const double dy = landmark.position.y - robot.y;
    const double true_range = std::sqrt(dx * dx + dy * dy);
    if (true_range > config_.sensor.max_range)
      continue;

    const double true_bearing =
        normalize_angle(std::atan2(dy, dx) - pose_.theta);
    if (std::abs(true_bearing) > config_.sensor.fov_half_angle)
      continue;

    Observation observation;
    observation.landmark_id = landmark.id;
    observation.true_range = true_range;
    observation.true_bearing = true_bearing;
    observation.range = std::max(
        kMinRange, true_range + sample_normal(config_.sensor.range_stddev));
    observation.bearing =
        normalize_angle(true_bearing +
                        sample_normal(config_.sensor.bearing_stddev));
    observations.push_back(observation);
  }

  return observations;
}

int Simulator2D::add_landmark(Vec2 position) {
  Landmark landmark;
  landmark.id = next_landmark_id_++;
  landmark.position = position;
  landmarks_.push_back(landmark);
  config_.landmarks = landmarks_;
  return landmark.id;
}

int Simulator2D::add_landmark(int id, Vec2 position) {
  if (id < 0)
    id = next_landmark_id_++;
  next_landmark_id_ = std::max(next_landmark_id_, id + 1);
  landmarks_.push_back({id, position});
  config_.landmarks = landmarks_;
  return id;
}

bool Simulator2D::remove_landmark(int id) {
  const auto it = std::find_if(
      landmarks_.begin(), landmarks_.end(),
      [id](const Landmark &landmark) { return landmark.id == id; });
  if (it == landmarks_.end())
    return false;

  landmarks_.erase(it);
  config_.landmarks = landmarks_;
  return true;
}

bool Simulator2D::remove_landmark_near(Vec2 point, double radius) {
  if (radius <= 0.0 || landmarks_.empty())
    return false;

  const double radius_sq = radius * radius;
  double best_sq = std::numeric_limits<double>::infinity();
  auto best = landmarks_.end();
  for (auto it = landmarks_.begin(); it != landmarks_.end(); ++it) {
    const double dist_sq = squared_distance(it->position, point);
    if (dist_sq < best_sq) {
      best_sq = dist_sq;
      best = it;
    }
  }

  if (best == landmarks_.end() || best_sq > radius_sq)
    return false;

  landmarks_.erase(best);
  config_.landmarks = landmarks_;
  return true;
}

void Simulator2D::set_pose(Pose2D pose) {
  pose.theta = normalize_angle(pose.theta);
  pose_ = pose;
  config_.initial_pose = pose;
}

void Simulator2D::set_sensor_config(SensorConfig sensor) {
  WorldConfig copy = config_;
  copy.sensor = sensor;
  validate_config(copy);
  config_.sensor = sensor;
}

void Simulator2D::set_odometry_config(OdometryConfig odometry) {
  WorldConfig copy = config_;
  copy.odometry = odometry;
  validate_config(copy);
  config_.odometry = odometry;
}

const Pose2D &Simulator2D::pose() const { return pose_; }

const std::vector<Landmark> &Simulator2D::landmarks() const {
  return landmarks_;
}

const SensorConfig &Simulator2D::sensor_config() const {
  return config_.sensor;
}

const OdometryConfig &Simulator2D::odometry_config() const {
  return config_.odometry;
}

double Simulator2D::time() const { return time_; }

std::uint64_t Simulator2D::step_index() const { return step_index_; }

void Simulator2D::validate_config(const WorldConfig &config) {
  if (config.sensor.max_range <= 0.0)
    throw std::invalid_argument("sensor.max_range must be positive");
  if (config.sensor.fov_half_angle <= 0.0 ||
      config.sensor.fov_half_angle > kPi)
    throw std::invalid_argument("sensor.fov_half_angle must be in (0, pi]");
  if (config.sensor.range_stddev < 0.0 ||
      config.sensor.bearing_stddev < 0.0)
    throw std::invalid_argument("sensor noise stddevs must be non-negative");
  if (config.odometry.translation_stddev < 0.0 ||
      config.odometry.rotation_stddev < 0.0)
    throw std::invalid_argument("odometry noise stddevs must be non-negative");
  if (config.time_step <= 0.0)
    throw std::invalid_argument("time_step must be positive");
}

Pose2D Simulator2D::integrate(Pose2D pose, Control control) {
  pose.x += control.translation * std::cos(pose.theta);
  pose.y += control.translation * std::sin(pose.theta);
  pose.theta = normalize_angle(pose.theta + control.rotation);
  return pose;
}

double Simulator2D::sample_normal(double stddev) {
  if (stddev == 0.0)
    return 0.0;
  std::normal_distribution<double> distribution(0.0, stddev);
  return distribution(rng_);
}

Control Simulator2D::sample_odometry(Control command) {
  command.translation += sample_normal(config_.odometry.translation_stddev);
  command.rotation += sample_normal(config_.odometry.rotation_stddev);
  return command;
}

void Simulator2D::seed_rng() {
  if (config_.use_random_seed) {
    std::random_device device;
    rng_.seed(device());
    return;
  }

  rng_.seed(config_.seed);
}

void Simulator2D::assign_missing_landmark_ids() {
  for (const Landmark &landmark : landmarks_) {
    if (landmark.id >= 0)
      next_landmark_id_ = std::max(next_landmark_id_, landmark.id + 1);
  }

  for (Landmark &landmark : landmarks_) {
    if (landmark.id < 0)
      landmark.id = next_landmark_id_++;
  }

  config_.landmarks = landmarks_;
}

WorldConfig make_default_world() {
  WorldConfig config;
  config.landmarks = {
      {-1, {2.5, 1.5}},   {-1, {4.5, -1.0}}, {-1, {0.5, 4.0}},
      {-1, {-2.5, 3.0}},  {-1, {-4.0, -1.5}}, {-1, {1.0, -3.5}},
  };
  return config;
}

} // namespace sim2d
