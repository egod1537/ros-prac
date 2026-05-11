#pragma once
#include "landmarkEKF.hpp"

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
