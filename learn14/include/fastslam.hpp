#pragma once

#include "particle.hpp"
#include "slam_types.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <cstdint>
#include <random>
#include <vector>

struct FastSLAM {
  std::vector<Particle> particles;
  double sigma_v, sigma_w, sigma_r, sigma_phi;
  double max_range;

  std::mt19937 rng;
  std::vector<Particle> resample_buf;
  std::vector<double> cdf_buf;

  FastSLAM() = default;
  FastSLAM(double sv, double sw, double sr, double sphi, uint32_t seed = 42);

  void init_gaussian(int M, double x0, double y0, double x1, double y1);

  void predict(double dist, double dtheta);
  void resample();
  void observe(const std::vector<Observation> &obs);

  Pose2D mean_pose() const;
  std::vector<Eigen::Vector2d> mean_landmarks() const;
  double effective_n() const;
  int size() const { return particles.size(); }
};
