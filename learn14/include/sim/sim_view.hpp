#pragma once
//
// #include "../mcl_omp.hpp"
// #include "sim2d.hpp"
//
// #include <GLFW/glfw3.h>
//
// #include <cstddef>
// #include <vector>
//
// class SimView {
// public:
//   SimView(GLFWwindow *win, Sim2D &sim, MCL &mcl, MCL_OMP &mcl_omp,
//           SimConfig &config);
//   ~SimView();
//
//   void render();
//
// private:
//   enum class MclMode {
//     Serial = 0,
//     OpenMP = 1,
//   };
//
//   struct PerformanceHistory {
//     std::vector<double> sample;
//     std::vector<double> predict_ms;
//     std::vector<double> measure_ms;
//     std::vector<double> observe_ms;
//     std::vector<double> total_ms;
//   };
//
//   void reset_();
//   void init_mcl_uniform_();
//   void init_mcl_gaussian_();
//   void sync_mcl_known_map_();
//   void sync_filter_config_();
//   void switch_mode_(MclMode mode);
//   void reset_mcl_history_();
//   void append_mcl_history_();
//   void update_estimate_trajectory_();
//   void reserve_particle_buffers_();
//   void teleport_robot_();
//   void handle_keyboard_();
//   void handle_teleop_speed_keys_();
//   void advance_auto_();
//   void render_layout_();
//   void step_periodic_(double &accum, double period, double dist,
//                       double dtheta);
//   void step_once_(double dist, double dtheta);
//
//   void render_config_();
//   void render_control_();
//   void render_space_();
//   void render_effective_n_();
//   void render_pose_error_();
//   void render_performance_();
//
//   const char *mode_label_() const;
//   bool using_openmp_() const;
//   std::vector<Particle> &active_particles_();
//   const std::vector<Particle> &active_particles_() const;
//   int active_size_() const;
//   int active_resample_count_() const;
//   double active_effective_n_() const;
//   Pose2D active_mean_pose_() const;
//   std::size_t active_known_map_size_() const;
//   void active_predict_(double dist, double dtheta);
//   void active_observe_(const std::vector<Observation> &observations);
//   PerformanceHistory &active_performance_();
//   const PerformanceHistory &active_performance_() const;
//   void clear_active_performance_();
//   void clear_all_performance_();
//   void append_performance_(double predict_ms, double measure_ms,
//                            double observe_ms, double total_ms);
//
//   GLFWwindow *window_ = nullptr;
//   SimConfig &config_;
//   Sim2D &sim_;
//   MCL &mcl_;
//   MCL_OMP &mcl_omp_;
//   MclMode mode_ = MclMode::Serial;
//
//   bool paused_ = true;
//   bool do_update_ = true;
//   int particle_count_ = 500;
//   int omp_thread_count_ = 1;
//   int omp_thread_limit_ = 1;
//   std::vector<double> particle_x_;
//   std::vector<double> particle_y_;
//   std::vector<double> history_step_;
//   std::vector<double> effective_n_history_;
//   std::vector<double> pose_error_history_;
//   PerformanceHistory serial_performance_;
//   PerformanceHistory openmp_performance_;
//   std::vector<Pose2D> estimate_trajectory_;
//   int mcl_step_ = 0;
//   double auto_accum_ = 0.0;
//   double auto_period_ = 0.08;
//   double auto_dist_ = 0.10;
//   double auto_dtheta_ = 0.025;
//   bool teleop_active_ = false;
//   double teleop_accum_ = 0.0;
//   double teleop_period_ = 0.08;
//   double manual_dist_ = 0.10;
//   double manual_dtheta_ = 0.08;
// };
