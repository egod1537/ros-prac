#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

struct LandmarkEKF {
  Eigen::Vector2d mu;
  Eigen::Matrix2d sigma;
  bool seen = false;
};
