#include "sim2d/sim.hpp"

#include <cassert>
#include <cmath>

namespace {
bool near(double a, double b, double eps = 1e-9) {
  return std::abs(a - b) <= eps;
}
} // namespace

int main() {
  sim2d::WorldConfig config;
  config.seed = 7;
  config.sensor.max_range = 3.0;
  config.sensor.fov_half_angle = sim2d::kPi / 2.0;
  config.sensor.range_stddev = 0.0;
  config.sensor.bearing_stddev = 0.0;
  config.odometry.translation_stddev = 0.0;
  config.odometry.rotation_stddev = 0.0;
  config.landmarks = {
      {10, {2.0, 0.0}},
      {11, {0.0, 3.0}},
  };

  sim2d::Simulator2D sim(config);
  const sim2d::StepResult result = sim.step({1.0, 0.0});

  assert(result.step_index == 1);
  assert(near(result.true_pose.x, 1.0));
  assert(near(result.true_pose.y, 0.0));
  assert(near(result.true_pose.theta, 0.0));
  assert(near(result.odometry.translation, 1.0));
  assert(near(result.odometry.rotation, 0.0));
  assert(result.observations.size() == 1);
  assert(result.observations[0].landmark_id == 10);
  assert(near(result.observations[0].range, 1.0));
  assert(near(result.observations[0].bearing, 0.0));

  const int new_id = sim.add_landmark({1.0, 1.0});
  assert(new_id == 12);
  assert(sim.remove_landmark_near({1.05, 1.0}, 0.1));
  assert(!sim.remove_landmark(999));

  return 0;
}
