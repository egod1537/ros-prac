#include "sim.hpp"
#include <cassert>
#include <cmath>
#include <random>

static std::mt19937 engine{std::random_device{}()};

double rng_next(double mean, double stddev) {
  std::normal_distribution<double> dist(mean, stddev);
  return dist(engine);
}

void sim_move(SimState &s, double u, double sigma_u) {
  s.true_robot_pos += u + rng_next(0, sigma_u);
}

double sim_measure(const SimState &s, int landmark_idx, double sigma_z) {
  assert(landmark_idx < s.true_landmark_pos.size());
  return s.true_landmark_pos[landmark_idx] - s.true_robot_pos +
         rng_next(0, sigma_z);
}
