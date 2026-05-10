#pragma once

#include "fastslam.hpp"
#include "imgui.h"
#include "slam_types.hpp"
#include <Eigen/Dense>
#include <random>
#include <vector>

struct GLFWwindow;

class SimView {
public:
  SimView();
  ~SimView();

  bool init(int window_width = 1600, int window_height = 1000);
  void run();

private:
  Pose2D robot_true;
  std::vector<Eigen::Vector2d> landmarks_true;

  FastSLAM filter;
  int M = 500;

  double linear_speed = 1.0;
  double angular_speed = 1.5;
  double sigma_v = 0.03;
  double sigma_w = 0.02;
  double sigma_r = 0.05;
  double sigma_phi = 0.03;
  double max_range = 7.0;
  double fov_half = 1.0471975511965976;
  int landmark_count = 8;
  int map_seed = 42;
  double landmark_min_x = -5.0;
  double landmark_max_x = 5.0;
  double landmark_min_y = -5.0;
  double landmark_max_y = 5.0;

  int selected_particle = 0;
  bool paused = false;
  bool show_particles = true;
  bool show_fov = true;
  bool show_ellipses = true;
  bool show_mean_landmarks = true;
  bool show_best_particle_map = true;

  static constexpr int HIST_LEN = 600;
  std::vector<float> hist_pose_rmse;
  std::vector<float> hist_lm_rmse;
  std::vector<float> hist_n_eff;
  int hist_idx = 0;

  mutable std::mt19937 rng;

  void step(double dt);
  void simulate_observations(std::vector<Observation> &obs) const;

  void handle_input();
  void render_world_panel();
  void render_timeseries_panel();
  void render_info_panel();

  void load_config();
  void save_config() const;
  void sanitize_config_values();
  void sync_filter_config();
  void restart_from_config();
  void reset_world_from_config();
  void refresh_filter_cache();

  void draw_robot_arrow(const Pose2D &p, ImU32 color, float scale = 0.3f);
  void draw_sensor_fov(const Pose2D &p);
  void draw_covariance_ellipse(const Eigen::Vector2d &mu,
                               const Eigen::Matrix2d &Sigma, ImU32 color);

  void init_filter_at_true();
  void reset_history();
  void update_history();
  int active_landmark_count() const;
  int majority_seen_landmark_count() const;
  double landmark_seen_weight(int id) const;
  bool delete_landmark_near(double x, double y, double radius);

  GLFWwindow *window = nullptr;
  bool glfw_initialized = false;
  bool ui_initialized = false;
  bool last_resampled = false;
  bool cache_dirty = true;
  int hist_count = 0;
  double frame_dt = 0.0;
  double step_dist = 0.0;
  double step_dtheta = 0.0;

  Pose2D cached_mean_pose;
  double cached_effective_n = 0.0;
  double cached_pose_rmse = 0.0;
  double cached_landmark_rmse = 0.0;
  int cached_active_landmark_count = 0;
  int cached_majority_seen_landmark_count = 0;
  int cached_best_particle = -1;
  std::vector<Eigen::Vector2d> cached_mean_landmarks;
  std::vector<Eigen::Vector2d> landmark_sum_buffer;
  std::vector<double> cached_landmark_seen_weights;

  std::vector<Observation> observation_buffer;
  std::vector<double> plot_x;
  std::vector<double> plot_y;
  std::vector<double> particle_plot_x;
  std::vector<double> particle_plot_y;
  std::vector<ImVec2> fov_points;
  std::vector<float> ellipse_x;
  std::vector<float> ellipse_y;
};
