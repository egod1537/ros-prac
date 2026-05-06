#pragma once

#include "sim2d.hpp"

#include <GLFW/glfw3.h>

class SimView {
public:
  SimView(GLFWwindow *win);
  ~SimView();

  void render();

private:
  void reset_();
  void handle_keyboard_();
  void handle_teleop_speed_keys_();
  void advance_auto_();
  void render_layout_();
  void step_periodic_(double &accum, double period, double dist,
                      double dtheta);
  void step_once_(double dist, double dtheta);

  void render_config_();
  void render_control_();
  void render_space_();
  void render_pmatrix_();
  void render_pvalues_();

  GLFWwindow *window_ = nullptr;
  SimConfig config_;
  Sim2D sim_;

  bool paused_ = true;
  bool do_update_ = true;
  double auto_accum_ = 0.0;
  double auto_period_ = 0.08;
  double auto_dist_ = 0.10;
  double auto_dtheta_ = 0.025;
  bool teleop_active_ = false;
  double teleop_accum_ = 0.0;
  double teleop_period_ = 0.08;
  double manual_dist_ = 0.10;
  double manual_dtheta_ = 0.08;
};
