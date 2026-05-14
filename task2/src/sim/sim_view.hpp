#pragma once

#include "sim2d.hpp"

#include <GLFW/glfw3.h>

#include <vector>

class MCL;

class SimView {
public:
  SimView(GLFWwindow *win, Sim2D &sim, MCL &mcl, SimConfig &config);
  ~SimView();

  void render();

private:
  void reset_();
  void init_mcl_uniform_();
  void init_mcl_gaussian_();
  void sync_mcl_known_map_();
  void observe_mcl_(const std::vector<Observation> &obs);
  void reset_mcl_history_();
  void append_mcl_history_();
  void update_estimate_trajectory_();
  void reserve_particle_buffers_();
  void teleport_robot_();
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
  void render_effective_n_();
  void render_pose_error_();

  GLFWwindow *window_ = nullptr;
  SimConfig &config_;
  Sim2D &sim_;
  MCL &mcl_;

  bool paused_ = true;
  bool do_update_ = true;
  int particle_count_ = 500;
  int resample_count_ = 0;
  std::vector<double> particle_x_;
  std::vector<double> particle_y_;
  std::vector<double> history_step_;
  std::vector<double> effective_n_history_;
  std::vector<double> pose_error_history_;
  std::vector<Pose2D> estimate_trajectory_;
  int mcl_step_ = 0;
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
