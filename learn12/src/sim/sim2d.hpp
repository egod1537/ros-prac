#pragma once

#include "../ekf2d.hpp"

#include <Eigen/Dense>

#include <random>
#include <vector>

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
  double sigma_r = 0.05;
  double sigma_phi = 0.03;
  double max_range = 7.0;
  double fov_half = 1.0471975511965976;
  std::vector<Eigen::Vector2d> initial_landmarks;
};

class Sim2D {
public:
  Sim2D();

  void init(const SimConfig &config);
  void step(double dist, double dtheta);
  std::vector<Observation> measure();
  void process_observations();

  void add_true_landmark(double x, double y);
  bool remove_true_landmark_near(double x, double y, double radius);

  Pose2D true_pose;
  std::vector<Eigen::Vector2d> true_landmarks;
  std::vector<Pose2D> trajectory_true;
  std::vector<Pose2D> trajectory_est;
  EKF2D ekf;
  SensorConfig sensor;
  MotionConfig motion;
  std::vector<int> true_to_ekf_idx;

private:
  std::mt19937 rng_;
};
