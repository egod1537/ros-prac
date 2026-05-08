#include <cmath>

constexpr int RX = 0, RY = 1, RT = 2;
inline int LX(int i) { return 3 + 2 * i; }
inline int LY(int i) { return 3 + 2 * i + 1; }

inline double wrap(double a) {
  a = std::fmod(a + M_PI, 2 * M_PI);
  if (a < 0)
    a += 2 * M_PI;
  return a - M_PI;
}

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
