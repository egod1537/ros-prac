#pragma once

#include "sim2d.hpp"

#include <GLFW/glfw3.h>
#include <vector>

class SimView {
public:
  SimView(GLFWwindow *win);

  void render();

private:
  void reset_();
  void handle_keyboard_();
  void step_once_(double dist, double dtheta);
  void append_diag_history_();

  void render_config_();
  void render_control_();
  void render_space_();
  void render_pmatrix_();
  void render_diag_history_();

  GLFWwindow *window_ = nullptr;
  SimConfig config_;
  Sim2D sim_;

  bool paused_ = true;
  bool do_update_ = true;
  double auto_accum_ = 0.0;
  double auto_period_ = 0.08;
  double auto_dist_ = 0.10;
  double auto_dtheta_ = 0.025;
  double manual_dist_ = 0.35;
  double manual_dtheta_ = 0.18;

  std::vector<double> diag_time_;
  std::vector<double> diag_px_;
  std::vector<double> diag_py_;
  std::vector<double> diag_ptheta_;
};
