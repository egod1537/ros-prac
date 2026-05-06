#pragma once

#include <cstdint>
#include <random>
#include <vector>

namespace sim2d {

constexpr double kPi = 3.141592653589793238462643383279502884;

double normalize_angle(double angle);

struct Vec2 {
  double x = 0.0;
  double y = 0.0;
};

struct Pose2D {
  double x = 0.0;
  double y = 0.0;
  double theta = 0.0;
};

struct Control {
  double translation = 0.0;
  double rotation = 0.0;
};

struct Landmark {
  int id = -1;
  Vec2 position;
};

struct SensorConfig {
  double max_range = 7.0;
  double fov_half_angle = kPi / 3.0;
  double range_stddev = 0.05;
  double bearing_stddev = 0.03;
};

struct OdometryConfig {
  double translation_stddev = 0.03;
  double rotation_stddev = 0.02;
};

struct WorldConfig {
  Pose2D initial_pose;
  std::vector<Landmark> landmarks;
  SensorConfig sensor;
  OdometryConfig odometry;
  double time_step = 1.0;
  std::uint32_t seed = 1;
  bool use_random_seed = false;
};

struct Observation {
  int landmark_id = -1;
  double range = 0.0;
  double bearing = 0.0;
  double true_range = 0.0;
  double true_bearing = 0.0;
};

struct StepResult {
  std::uint64_t step_index = 0;
  double time = 0.0;
  Pose2D true_pose;
  Control command;
  Control odometry;
  std::vector<Observation> observations;
};

class Simulator2D {
public:
  explicit Simulator2D(WorldConfig config = WorldConfig{});

  void reset();
  void reset(WorldConfig config);

  StepResult step(Control command, bool collect_observations = true);
  std::vector<Observation> sense();

  int add_landmark(Vec2 position);
  int add_landmark(int id, Vec2 position);
  bool remove_landmark(int id);
  bool remove_landmark_near(Vec2 point, double radius);

  void set_pose(Pose2D pose);
  void set_sensor_config(SensorConfig sensor);
  void set_odometry_config(OdometryConfig odometry);

  const Pose2D &pose() const;
  const std::vector<Landmark> &landmarks() const;
  const SensorConfig &sensor_config() const;
  const OdometryConfig &odometry_config() const;
  double time() const;
  std::uint64_t step_index() const;

private:
  static void validate_config(const WorldConfig &config);
  static Pose2D integrate(Pose2D pose, Control control);

  double sample_normal(double stddev);
  Control sample_odometry(Control command);
  void seed_rng();
  void assign_missing_landmark_ids();

  WorldConfig config_;
  Pose2D pose_;
  std::vector<Landmark> landmarks_;
  std::mt19937 rng_;
  double time_ = 0.0;
  std::uint64_t step_index_ = 0;
  int next_landmark_id_ = 0;
};

WorldConfig make_default_world();

} // namespace sim2d
