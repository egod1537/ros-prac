#pragma once

#include <Eigen/Dense>

#include <random>
#include <vector>

struct alignas(64) Particle {
  double x, y, theta;
  double weight;
  double log_weight;
};
struct Pose2D {
  double x = 0.0;
  double y = 0.0;
  double theta = 0.0;
};

struct Observation {
  int id = -1;
  double r = 0.0;
  double phi = 0.0;
};

struct SensorConfig {
  double max_range = 7.0;
  double fov_half = 1.0471975511965976;
  double sigma_r = 0.05;
  double sigma_phi = 0.03;
};

struct MotionConfig {
  double sigma_v = 0.03;
  double sigma_w = 0.02;
};

struct SimConfig {
  double sigma_v = 0.03;
  double sigma_w = 0.02;

  double max_range = 7.0;
  double fov_half = 1.0471975511965976;
  double sigma_r = 0.05;
  double sigma_phi = 0.03;

  int landmark_count = 6;
  double landmark_min_x = -5.0;
  double landmark_max_x = 5.0;
  double landmark_min_y = -5.0;
  double landmark_max_y = 5.0;
};

class Sim2D {
public:
  Sim2D();

  void init(const SimConfig &config);
  void step(double dist, double dtheta);
  std::vector<Observation> measure();

  void add_true_landmark(double x, double y);
  bool remove_true_landmark_near(double x, double y, double radius);

  Pose2D true_pose;
  std::vector<Eigen::Vector2d> true_landmarks;
  std::vector<Pose2D> trajectory_true;
  SensorConfig sensor;
  MotionConfig motion;

private:
  std::mt19937 rng_;
};
