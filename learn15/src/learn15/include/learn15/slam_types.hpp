#pragma once

struct Observation {
  int id = -1;
  double r = 0.0;
  double phi = 0.0;
};

struct Particle {
  double x, y, theta;
  double weight, log_weight;
};

struct Pose2D {
  double x = 0.0;
  double y = 0.0;
  double theta = 0.0;
};
