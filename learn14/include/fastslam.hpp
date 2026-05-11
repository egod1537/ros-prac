#pragma once

#include "particle.hpp"
#include "slam_types.hpp"
#include <Eigen/Dense>
#include <cstdint>
#include <random>
#include <vector>

struct FastSLAM {
  std::vector<Particle> particles;
  double sigma_v = 0.0;
  double sigma_w = 0.0;
  double sigma_r = 0.0;
  double sigma_phi = 0.0;
  double max_range = 0.0;
  bool last_resampled = false;
  double last_effective_n = 0.0;
  double last_effective_n_after_resample = 0.0;
  double last_log_weight_min = 0.0;
  double last_log_weight_max = 0.0;
  double last_log_weight_span = 0.0;

  std::mt19937 rng;
  std::vector<Particle> resample_buf;
  std::vector<double> cdf_buf;

  FastSLAM() = default;
  FastSLAM(double sv, double sw, double sr, double sphi, uint32_t seed = 42);

  void init_gaussian(int M, double x0, double y0, double th0, double std);

  void predict(double dist, double dtheta);
  void resample();
  void observe(const std::vector<Observation> &obs);

  Pose2D mean_pose() const;
  std::vector<Eigen::Vector2d> mean_landmarks() const;
  double effective_n() const;
  int size() const { return particles.size(); }
};
