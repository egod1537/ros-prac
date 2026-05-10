#pragma once

#include <Eigen/Dense>

struct LandmarkEKF {
  Eigen::Vector2d mu;
  Eigen::Matrix2d sigma;
  bool seen = false;
};
