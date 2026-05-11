#pragma once
#include "landmarkEKF.hpp"
#include <vector>

struct alignas(64) Particle {
  double x, y, theta;
  double weight, log_weight;
  std::vector<LandmarkEKF> landmarks;

  double update_landmark(int idx, double r, double phi, double sigma_r,
                         double sigma_phi);
  void init_landmark(int idx, double r, double phi, double sigma_r,
                     double sigma_phi);
  bool is_known(int idx) const;
  void ensure_capacity(int idx);
};
