#pragma once
#include <vector>

struct SimState {
  double true_robot_pos;
  std::vector<double> true_landmark_pos;
  double time;

  size_t get_landmark_count() const { return true_landmark_pos.size(); }
};

void sim_move(SimState &s, double u, double sigma_u);
double sim_measure(const SimState &s, int landmark_idx, double sigma_z);
