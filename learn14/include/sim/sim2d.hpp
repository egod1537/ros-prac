#pragma once

#include "slam_types.hpp"
#include <Eigen/Dense>
#include <random>
#include <vector>

struct SimConfig {
  int particle_count = 500;
  double linear_speed = 1.0;
  double angular_speed = 1.5;

  double sigma_v = 0.03;
  double sigma_w = 0.02;

  double max_range = 7.0;
  double fov_half = 1.0471975511965976;
  double sigma_r = 0.05;
  double sigma_phi = 0.03;

  int landmark_count = 8;
  int map_seed = 42;
  double landmark_min_x = -5.0;
  double landmark_max_x = 5.0;
  double landmark_min_y = -5.0;
  double landmark_max_y = 5.0;

  bool show_particles = true;
  bool show_fov = true;
  bool show_ellipses = true;
  bool show_mean_landmarks = true;
  bool show_best_particle_map = true;
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
