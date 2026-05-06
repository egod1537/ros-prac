#include "sim2d.hpp"

#include "../geom.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

namespace {
constexpr double kMinRange = 1e-6;

Pose2D estimate_pose_from(const EKF2D &ekf) {
  Pose2D pose;
  if (ekf.x.size() >= 3) {
    pose.x = ekf.x(RX);
    pose.y = ekf.x(RY);
    pose.theta = ekf.x(RT);
  }
  return pose;
}

int next_available_landmark_id(const EKF2D &ekf,
                               const std::vector<int> &true_to_ekf_idx) {
  int next_id = ekf.get_landmark_count();
  for (int mapped_idx : true_to_ekf_idx) {
    if (mapped_idx >= next_id)
      next_id = mapped_idx + 1;
  }
  return next_id;
}

bool visible_measurement(const Pose2D &pose, const SensorConfig &sensor,
                         const Eigen::Vector2d &landmark, double &range,
                         double &bearing) {
  const Eigen::Vector2d delta(landmark.x() - pose.x, landmark.y() - pose.y);
  range = delta.norm();
  if (range > sensor.max_range)
    return false;

  bearing = wrap(std::atan2(delta.y(), delta.x()) - pose.theta);
  return std::abs(bearing) <= sensor.fov_half;
}

Observation make_noisy_observation(int id, double range, double bearing,
                                   std::normal_distribution<double> &r_noise,
                                   std::normal_distribution<double> &phi_noise,
                                   std::mt19937 &rng) {
  Observation obs;
  obs.id = id;
  obs.r = std::max(kMinRange, range + r_noise(rng));
  obs.phi = wrap(bearing + phi_noise(rng));
  return obs;
}

std::vector<Eigen::Vector2d> generate_landmarks(const SimConfig &config,
                                                std::mt19937 &rng) {
  const int count = std::clamp(config.landmark_count, 0, 1000);
  const double min_x = std::min(config.landmark_min_x, config.landmark_max_x);
  const double max_x = std::max(config.landmark_min_x, config.landmark_max_x);
  const double min_y = std::min(config.landmark_min_y, config.landmark_max_y);
  const double max_y = std::max(config.landmark_min_y, config.landmark_max_y);

  std::uniform_real_distribution<double> x_dist(min_x, max_x);
  std::uniform_real_distribution<double> y_dist(min_y, max_y);

  std::vector<Eigen::Vector2d> landmarks;
  landmarks.reserve(static_cast<std::size_t>(count));
  for (int i = 0; i < count; ++i)
    landmarks.emplace_back(x_dist(rng), y_dist(rng));
  return landmarks;
}
} // namespace

Sim2D::Sim2D() : rng_(std::random_device{}()) {}

void Sim2D::init(const SimConfig &config) {
  true_pose = {};
  true_landmarks = generate_landmarks(config, rng_);
  true_to_ekf_idx.assign(true_landmarks.size(), -1);

  motion.sigma_v = config.sigma_v;
  motion.sigma_w = config.sigma_w;
  sensor.max_range = config.max_range;
  sensor.fov_half = config.fov_half;
  sensor.sigma_r = config.sigma_r;
  sensor.sigma_phi = config.sigma_phi;

  ekf = EKF2D(motion.sigma_v, motion.sigma_w, sensor.sigma_r,
              sensor.sigma_phi);
  ekf.max_range = sensor.max_range;

  trajectory_true.clear();
  trajectory_est.clear();
  trajectory_true.push_back(true_pose);
  trajectory_est.push_back(estimate_pose_from(ekf));
}

void Sim2D::step(double dist, double dtheta) {
  true_pose.x += dist * std::cos(true_pose.theta);
  true_pose.y += dist * std::sin(true_pose.theta);
  true_pose.theta = wrap(true_pose.theta + dtheta);

  std::normal_distribution<double> v_noise(0.0, motion.sigma_v);
  std::normal_distribution<double> w_noise(0.0, motion.sigma_w);
  ekf.predict(dist + v_noise(rng_), dtheta + w_noise(rng_));

  trajectory_true.push_back(true_pose);
  trajectory_est.push_back(estimate_pose_from(ekf));
}

std::vector<Observation> Sim2D::measure() {
  std::vector<Observation> observations;
  std::normal_distribution<double> r_noise(0.0, sensor.sigma_r);
  std::normal_distribution<double> phi_noise(0.0, sensor.sigma_phi);

  int next_new_idx = next_available_landmark_id(ekf, true_to_ekf_idx);

  for (std::size_t i = 0; i < true_landmarks.size(); ++i) {
    double r = 0.0;
    double phi = 0.0;
    if (!visible_measurement(true_pose, sensor, true_landmarks[i], r, phi))
      continue;

    if (true_to_ekf_idx[i] < 0)
      true_to_ekf_idx[i] = next_new_idx++;

    observations.push_back(make_noisy_observation(
        true_to_ekf_idx[i], r, phi, r_noise, phi_noise, rng_));
  }

  return observations;
}

void Sim2D::process_observations() {
  const std::vector<Observation> observations = measure();
  for (const Observation &obs : observations)
    ekf.observe(obs.id, obs.r, obs.phi);

  if (!trajectory_est.empty())
    trajectory_est.back() = estimate_pose_from(ekf);
}

void Sim2D::add_true_landmark(double x, double y) {
  true_landmarks.emplace_back(x, y);
  true_to_ekf_idx.push_back(-1);
}

bool Sim2D::remove_true_landmark_near(double x, double y, double radius) {
  if (true_landmarks.empty() || radius <= 0.0)
    return false;

  const Eigen::Vector2d target(x, y);
  double best_dist = std::numeric_limits<double>::infinity();
  std::size_t best_idx = true_landmarks.size();

  for (std::size_t i = 0; i < true_landmarks.size(); ++i) {
    const double dist = (true_landmarks[i] - target).norm();
    if (dist < best_dist) {
      best_dist = dist;
      best_idx = i;
    }
  }

  if (best_idx == true_landmarks.size() || best_dist > radius)
    return false;

  true_landmarks.erase(true_landmarks.begin() +
                       static_cast<std::ptrdiff_t>(best_idx));
  true_to_ekf_idx.erase(true_to_ekf_idx.begin() +
                        static_cast<std::ptrdiff_t>(best_idx));
  return true;
}
