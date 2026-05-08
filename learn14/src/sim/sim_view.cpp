#include "sim_view.hpp"

#include "sim_config.hpp"
#include "timing.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <Eigen/Dense>
#include <omp.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr int kMaxStepsPerFrame = 4;
constexpr float kWorldPanelW = 620.0f;
constexpr float kWorldPanelH = 630.0f;
constexpr float kWorldPlotSize = 600.0f;
constexpr float kSmallPanelH = 300.0f;
constexpr float kEffectiveNPanelW = 410.0f;
constexpr float kPoseErrorPanelW = 520.0f;
constexpr float kPerformancePanelW = 940.0f;
constexpr float kSmallPlotH = 260.0f;
constexpr double kManualStepMin = 0.001;
constexpr double kManualDistMax = 1.0;
constexpr double kManualDthetaMax = 0.8;
constexpr double kSpeedScaleUp = 1.1;
constexpr double kSpeedScaleDown = 0.9;
constexpr int kParticleCountMin = 10;
constexpr int kParticleCountMax = 200000;

struct TeleopAxes {
  double linear = 0.0;
  double angular = 0.0;

  bool active() const { return linear != 0.0 || angular != 0.0; }
};

bool slider_double(const char *label, double *value, double min_value,
                   double max_value, const char *format = "%.3f") {
  return ImGui::SliderScalar(label, ImGuiDataType_Double, value, &min_value,
                             &max_value, format);
}

void slider_range(const char *min_label, double *min_value,
                  const char *max_label, double *max_value, double lower_bound,
                  double upper_bound, const char *format = "%.2f") {
  slider_double(min_label, min_value, lower_bound, upper_bound, format);
  if (*min_value > *max_value)
    *max_value = *min_value;
  slider_double(max_label, max_value, lower_bound, upper_bound, format);
  if (*max_value < *min_value)
    *min_value = *max_value;
}

ImU32 rgba(int r, int g, int b, int a = 255) { return IM_COL32(r, g, b, a); }

ImVec2 plot_to_pixels(const Eigen::Vector2d &p) {
  return ImPlot::PlotToPixels(p.x(), p.y());
}

bool key_down(ImGuiKey key) { return ImGui::IsKeyDown(key); }

bool key_pressed(ImGuiKey key) { return ImGui::IsKeyPressed(key, false); }

void scale_step(double &value, double factor, double max_value) {
  value = std::clamp(value * factor, kManualStepMin, max_value);
}

template <typename Filter>
void configure_filter(Filter &filter, const SimConfig &config) {
  filter.sigma_v = config.sigma_v;
  filter.sigma_w = config.sigma_w;
  filter.sigma_r = config.sigma_r;
  filter.sigma_phi = config.sigma_phi;
  filter.max_range = config.max_range;
}

template <typename Filter>
void sync_known_map(Filter &filter, const Sim2D &sim) {
  filter.known_map.assign(sim.true_landmarks.begin(), sim.true_landmarks.end());
}

template <typename Src, typename Dst>
void copy_filter_state(const Src &src, Dst &dst) {
  dst.particles = src.particles;
  dst.known_map = src.known_map;
  dst.sigma_v = src.sigma_v;
  dst.sigma_w = src.sigma_w;
  dst.sigma_r = src.sigma_r;
  dst.sigma_phi = src.sigma_phi;
  dst.max_range = src.max_range;
  dst.resample_count = src.resample_count;
  dst.resample_buffer.clear();
  dst.resample_buffer.reserve(dst.particles.size());
  dst.cdf_buffer.clear();
  dst.cdf_buffer.reserve(dst.particles.size());
}

TeleopAxes read_teleop_axes() {
  TeleopAxes axes;
  const bool forward = key_down(ImGuiKey_W) || key_down(ImGuiKey_I) ||
                       key_down(ImGuiKey_UpArrow);
  const bool backward = key_down(ImGuiKey_S) || key_down(ImGuiKey_Comma) ||
                        key_down(ImGuiKey_DownArrow);
  const bool left = key_down(ImGuiKey_A) || key_down(ImGuiKey_J) ||
                    key_down(ImGuiKey_LeftArrow);
  const bool right = key_down(ImGuiKey_D) || key_down(ImGuiKey_L) ||
                     key_down(ImGuiKey_RightArrow);

  axes.linear = (forward ? 1.0 : 0.0) - (backward ? 1.0 : 0.0);
  axes.angular = (left ? 1.0 : 0.0) - (right ? 1.0 : 0.0);
  return axes;
}

void add_world_line(ImDrawList *draw, const Eigen::Vector2d &a,
                    const Eigen::Vector2d &b, ImU32 color,
                    float thickness = 1.0f) {
  draw->AddLine(plot_to_pixels(a), plot_to_pixels(b), color, thickness);
}

void draw_dashed_segment(ImDrawList *draw, ImVec2 a, ImVec2 b, ImU32 color,
                         float thickness) {
  const float dx = b.x - a.x;
  const float dy = b.y - a.y;
  const float len = std::sqrt(dx * dx + dy * dy);
  if (len <= 1.0f)
    return;

  constexpr float dash = 7.0f;
  constexpr float gap = 5.0f;
  float t = 0.0f;
  while (t < len) {
    const float next = std::min(t + dash, len);
    const float t0 = t / len;
    const float t1 = next / len;
    draw->AddLine(ImVec2(a.x + dx * t0, a.y + dy * t0),
                  ImVec2(a.x + dx * t1, a.y + dy * t1), color, thickness);
    t = next + gap;
  }
}

void draw_trajectory(ImDrawList *draw, const std::vector<Pose2D> &poses,
                     ImU32 color, float thickness, bool dashed) {
  if (poses.size() < 2)
    return;

  std::vector<ImVec2> points;
  points.reserve(poses.size());
  for (const Pose2D &pose : poses)
    points.push_back(ImPlot::PlotToPixels(pose.x, pose.y));

  if (!dashed) {
    draw->AddPolyline(points.data(), static_cast<int>(points.size()), color, 0,
                      thickness);
    return;
  }

  for (std::size_t i = 1; i < points.size(); ++i)
    draw_dashed_segment(draw, points[i - 1], points[i], color, thickness);
}

void draw_pose_arrow(ImDrawList *draw, const Pose2D &pose, ImU32 fill,
                     ImU32 outline) {
  const double s = 0.35;
  const Eigen::Vector2d forward(std::cos(pose.theta), std::sin(pose.theta));
  const Eigen::Vector2d left(-std::sin(pose.theta), std::cos(pose.theta));
  const Eigen::Vector2d center(pose.x, pose.y);
  const Eigen::Vector2d tip = center + s * forward;
  const Eigen::Vector2d base = center - 0.45 * s * forward;
  const Eigen::Vector2d p1 = base + 0.55 * s * left;
  const Eigen::Vector2d p2 = base - 0.55 * s * left;

  draw->AddTriangleFilled(plot_to_pixels(tip), plot_to_pixels(p1),
                          plot_to_pixels(p2), fill);
  draw->AddTriangle(plot_to_pixels(tip), plot_to_pixels(p1), plot_to_pixels(p2),
                    outline, 1.5f);
}

void draw_fov(ImDrawList *draw, const Pose2D &pose,
              const SensorConfig &sensor) {
  const int segments = 64;
  const ImU32 fill = rgba(64, 132, 214, 34);
  const ImU32 line = rgba(64, 132, 214, 120);
  const Eigen::Vector2d center(pose.x, pose.y);

  if (sensor.fov_half >= kPi - 1e-4) {
    std::vector<ImVec2> circle;
    circle.reserve(segments);
    for (int i = 0; i < segments; ++i) {
      const double a = pose.theta + 2.0 * kPi * i / segments;
      circle.push_back(ImPlot::PlotToPixels(
          pose.x + sensor.max_range * std::cos(a),
          pose.y + sensor.max_range * std::sin(a)));
    }
    draw->AddConvexPolyFilled(circle.data(), static_cast<int>(circle.size()),
                              fill);
    draw->AddPolyline(circle.data(), static_cast<int>(circle.size()), line,
                      ImDrawFlags_Closed, 1.0f);
    return;
  }

  draw->PathLineTo(plot_to_pixels(center));
  std::vector<ImVec2> arc;
  arc.reserve(segments + 1);
  for (int i = 0; i <= segments; ++i) {
    const double u = static_cast<double>(i) / static_cast<double>(segments);
    const double a =
        pose.theta - sensor.fov_half + 2.0 * sensor.fov_half * u;
    const Eigen::Vector2d p(pose.x + sensor.max_range * std::cos(a),
                            pose.y + sensor.max_range * std::sin(a));
    const ImVec2 px = plot_to_pixels(p);
    draw->PathLineTo(px);
    arc.push_back(px);
  }
  draw->PathFillConcave(fill);

  add_world_line(draw, center,
                 center + sensor.max_range *
                              Eigen::Vector2d(std::cos(pose.theta -
                                                       sensor.fov_half),
                                              std::sin(pose.theta -
                                                       sensor.fov_half)),
                 line);
  add_world_line(draw, center,
                 center + sensor.max_range *
                              Eigen::Vector2d(std::cos(pose.theta +
                                                       sensor.fov_half),
                                              std::sin(pose.theta +
                                                       sensor.fov_half)),
                 line);
  draw->AddPolyline(arc.data(), static_cast<int>(arc.size()), line, 0, 1.0f);
}

struct Bounds {
  double min_x = -5.0;
  double max_x = 5.0;
  double min_y = -5.0;
  double max_y = 5.0;

  void add(double x, double y) {
    min_x = std::min(min_x, x);
    max_x = std::max(max_x, x);
    min_y = std::min(min_y, y);
    max_y = std::max(max_y, y);
  }
};

template <typename Filter>
Bounds compute_world_bounds(const Sim2D &sim,
                            const std::vector<Pose2D> &estimate_trajectory,
                            const Filter &filter) {
  Bounds bounds;
  bounds.add(sim.true_pose.x - sim.sensor.max_range,
             sim.true_pose.y - sim.sensor.max_range);
  bounds.add(sim.true_pose.x + sim.sensor.max_range,
             sim.true_pose.y + sim.sensor.max_range);

  for (const Eigen::Vector2d &lm : sim.true_landmarks)
    bounds.add(lm.x(), lm.y());
  for (const Pose2D &pose : sim.trajectory_true)
    bounds.add(pose.x, pose.y);
  for (const Pose2D &pose : estimate_trajectory)
    bounds.add(pose.x, pose.y);

  const Pose2D mean = filter.mean_pose();
  bounds.add(mean.x, mean.y);
  for (const Particle &p : filter.particles)
    bounds.add(p.x, p.y);

  constexpr double pad = 1.0;
  bounds.min_x -= pad;
  bounds.max_x += pad;
  bounds.min_y -= pad;
  bounds.max_y += pad;

  const double center_x = 0.5 * (bounds.min_x + bounds.max_x);
  const double center_y = 0.5 * (bounds.min_y + bounds.max_y);
  const double half_span =
      0.5 * std::max(bounds.max_x - bounds.min_x, bounds.max_y - bounds.min_y);
  bounds.min_x = center_x - half_span;
  bounds.max_x = center_x + half_span;
  bounds.min_y = center_y - half_span;
  bounds.max_y = center_y + half_span;
  return bounds;
}
} // namespace

SimView::SimView(GLFWwindow *win, Sim2D &sim, MCL &mcl, MCL_OMP &mcl_omp,
                 SimConfig &config)
    : window_(win), config_(config), sim_(sim), mcl_(mcl),
      mcl_omp_(mcl_omp) {
  omp_thread_limit_ =
      std::max(1, static_cast<int>(mcl_omp_.thread_rngs.size()));
  omp_thread_count_ =
      std::clamp(omp_get_max_threads(), 1, omp_thread_limit_);
  omp_set_num_threads(omp_thread_count_);
  sync_filter_config_();
  sync_mcl_known_map_();

  if (active_size_() > 0)
    particle_count_ = active_size_();
  else
    init_mcl_gaussian_();
  reserve_particle_buffers_();
  update_estimate_trajectory_();
  reset_mcl_history_();
}

SimView::~SimView() {
  sim_config::sanitize(config_);
  sim_config::save(config_);
}

const char *SimView::mode_label_() const {
  return using_openmp_() ? "MCL_OMP" : "MCL";
}

bool SimView::using_openmp_() const { return mode_ == MclMode::OpenMP; }

std::vector<Particle> &SimView::active_particles_() {
  return using_openmp_() ? mcl_omp_.particles : mcl_.particles;
}

const std::vector<Particle> &SimView::active_particles_() const {
  return using_openmp_() ? mcl_omp_.particles : mcl_.particles;
}

int SimView::active_size_() const {
  return using_openmp_() ? mcl_omp_.size() : mcl_.size();
}

int SimView::active_resample_count_() const {
  return using_openmp_() ? mcl_omp_.resample_count : mcl_.resample_count;
}

double SimView::active_effective_n_() const {
  return using_openmp_() ? mcl_omp_.effective_n() : mcl_.effective_n();
}

Pose2D SimView::active_mean_pose_() const {
  return using_openmp_() ? mcl_omp_.mean_pose() : mcl_.mean_pose();
}

std::size_t SimView::active_known_map_size_() const {
  return using_openmp_() ? mcl_omp_.known_map.size() : mcl_.known_map.size();
}

void SimView::active_predict_(double dist, double dtheta) {
  if (using_openmp_())
    mcl_omp_.predict(dist, dtheta);
  else
    mcl_.predict(dist, dtheta);
}

void SimView::active_observe_(const std::vector<Observation> &observations) {
  if (using_openmp_())
    mcl_omp_.observe(observations);
  else
    mcl_.observe(observations);
}

SimView::PerformanceHistory &SimView::active_performance_() {
  return using_openmp_() ? openmp_performance_ : serial_performance_;
}

const SimView::PerformanceHistory &SimView::active_performance_() const {
  return using_openmp_() ? openmp_performance_ : serial_performance_;
}

void SimView::clear_active_performance_() {
  PerformanceHistory &perf = active_performance_();
  perf.sample.clear();
  perf.predict_ms.clear();
  perf.measure_ms.clear();
  perf.observe_ms.clear();
  perf.total_ms.clear();
}

void SimView::clear_all_performance_() {
  const MclMode saved_mode = mode_;
  mode_ = MclMode::Serial;
  clear_active_performance_();
  mode_ = MclMode::OpenMP;
  clear_active_performance_();
  mode_ = saved_mode;
}

void SimView::append_performance_(double predict_ms, double measure_ms,
                                  double observe_ms, double total_ms) {
  PerformanceHistory &perf = active_performance_();
  perf.sample.push_back(static_cast<double>(perf.sample.size()));
  perf.predict_ms.push_back(predict_ms);
  perf.measure_ms.push_back(measure_ms);
  perf.observe_ms.push_back(observe_ms);
  perf.total_ms.push_back(total_ms);
}

void SimView::render() {
  glfwPollEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  handle_keyboard_();
  advance_auto_();
  render_layout_();

  ImGui::Render();
  int display_w = 0;
  int display_h = 0;
  glfwGetFramebufferSize(window_, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(0.08f, 0.09f, 0.10f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glfwSwapBuffers(window_);
}

void SimView::advance_auto_() {
  if (!paused_)
    step_periodic_(auto_accum_, auto_period_, auto_dist_, auto_dtheta_);
}

void SimView::render_layout_() {
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
  ImGui::SetNextWindowSize(viewport->WorkSize, ImGuiCond_Always);
  ImGui::Begin("learn13 SimView", nullptr,
               ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoResize);

  const float left_width = 310.0f;
  ImGui::BeginChild("left", ImVec2(left_width, 0), ImGuiChildFlags_Borders);
  render_config_();
  ImGui::Separator();
  render_control_();
  ImGui::EndChild();

  ImGui::SameLine();
  ImGui::BeginChild("right", ImVec2(0, 0), 0,
                    ImGuiWindowFlags_HorizontalScrollbar);
  ImGui::BeginChild("world", ImVec2(kWorldPanelW, kWorldPanelH),
                    ImGuiChildFlags_Borders);
  render_space_();
  ImGui::EndChild();

  ImGui::BeginChild("effective_n", ImVec2(kEffectiveNPanelW, kSmallPanelH),
                    ImGuiChildFlags_Borders);
  render_effective_n_();
  ImGui::EndChild();

  ImGui::SameLine();
  ImGui::BeginChild("pose_error", ImVec2(kPoseErrorPanelW, kSmallPanelH),
                    ImGuiChildFlags_Borders);
  render_pose_error_();
  ImGui::EndChild();

  ImGui::BeginChild("performance", ImVec2(kPerformancePanelW, kSmallPanelH),
                    ImGuiChildFlags_Borders);
  render_performance_();
  ImGui::EndChild();
  ImGui::EndChild();

  ImGui::End();
}

void SimView::reset_() {
  sim_config::sanitize(config_);
  sim_config::save(config_);
  sim_.init(config_);
  sync_filter_config_();
  init_mcl_gaussian_();
  clear_all_performance_();

  auto_accum_ = 0.0;
  teleop_active_ = false;
  teleop_accum_ = 0.0;
}

void SimView::init_mcl_uniform_() {
  sync_mcl_known_map_();

  Bounds bounds;
  bounds.min_x = std::min(config_.landmark_min_x, config_.landmark_max_x);
  bounds.max_x = std::max(config_.landmark_min_x, config_.landmark_max_x);
  bounds.min_y = std::min(config_.landmark_min_y, config_.landmark_max_y);
  bounds.max_y = std::max(config_.landmark_min_y, config_.landmark_max_y);
  bounds.add(sim_.true_pose.x, sim_.true_pose.y);
  for (const Eigen::Vector2d &lm : sim_.true_landmarks)
    bounds.add(lm.x(), lm.y());

  constexpr double pad = 1.0;
  particle_count_ =
      std::clamp(particle_count_, kParticleCountMin, kParticleCountMax);
  if (using_openmp_())
    mcl_omp_.init_uniform(particle_count_, bounds.min_x - pad,
                          bounds.max_x + pad, bounds.min_y - pad,
                          bounds.max_y + pad);
  else
    mcl_.init_uniform(particle_count_, bounds.min_x - pad, bounds.max_x + pad,
                      bounds.min_y - pad, bounds.max_y + pad);
  reserve_particle_buffers_();
  reset_mcl_history_();
  clear_active_performance_();
}

void SimView::init_mcl_gaussian_() {
  sync_mcl_known_map_();
  particle_count_ =
      std::clamp(particle_count_, kParticleCountMin, kParticleCountMax);
  if (using_openmp_())
    mcl_omp_.init_gaussian(particle_count_, sim_.true_pose.x,
                           sim_.true_pose.y, sim_.true_pose.theta, 0.1);
  else
    mcl_.init_gaussian(particle_count_, sim_.true_pose.x, sim_.true_pose.y,
                       sim_.true_pose.theta, 0.1);
  reserve_particle_buffers_();
  reset_mcl_history_();
  clear_active_performance_();
}

void SimView::sync_mcl_known_map_() {
  sync_known_map(mcl_, sim_);
  sync_known_map(mcl_omp_, sim_);
}

void SimView::sync_filter_config_() {
  configure_filter(mcl_, config_);
  configure_filter(mcl_omp_, config_);
}

void SimView::switch_mode_(MclMode mode) {
  if (mode_ == mode)
    return;

  if (mode == MclMode::OpenMP)
    copy_filter_state(mcl_, mcl_omp_);
  else
    copy_filter_state(mcl_omp_, mcl_);

  mode_ = mode;
  particle_count_ = active_size_();
  reserve_particle_buffers_();
  update_estimate_trajectory_();
}

void SimView::reset_mcl_history_() {
  estimate_trajectory_.clear();
  estimate_trajectory_.push_back(active_mean_pose_());

  history_step_.clear();
  effective_n_history_.clear();
  pose_error_history_.clear();
  history_step_.reserve(4096);
  effective_n_history_.reserve(4096);
  pose_error_history_.reserve(4096);
  mcl_step_ = 0;
  append_mcl_history_();
}

void SimView::append_mcl_history_() {
  const Pose2D mean = active_mean_pose_();
  const double dx = sim_.true_pose.x - mean.x;
  const double dy = sim_.true_pose.y - mean.y;
  history_step_.push_back(static_cast<double>(mcl_step_));
  effective_n_history_.push_back(active_effective_n_());
  pose_error_history_.push_back(std::hypot(dx, dy));
}

void SimView::update_estimate_trajectory_() {
  const Pose2D mean = active_mean_pose_();
  if (estimate_trajectory_.empty()) {
    estimate_trajectory_.push_back(mean);
    return;
  }
  if (estimate_trajectory_.size() < sim_.trajectory_true.size())
    estimate_trajectory_.push_back(mean);
  else
    estimate_trajectory_.back() = mean;
}

void SimView::reserve_particle_buffers_() {
  const std::size_t count = active_particles_().size();
  if (particle_x_.capacity() < count)
    particle_x_.reserve(count);
  if (particle_y_.capacity() < count)
    particle_y_.reserve(count);
}

void SimView::teleport_robot_() {
  sim_.true_pose.x += 5.0;
  sim_.trajectory_true.push_back(sim_.true_pose);
  update_estimate_trajectory_();
  ++mcl_step_;
  append_mcl_history_();
}

void SimView::handle_keyboard_() {
  if (ImGui::GetIO().WantTextInput)
    return;

  if (key_pressed(ImGuiKey_Space))
    paused_ = !paused_;
  if (key_pressed(ImGuiKey_R))
    init_mcl_uniform_();
  if (key_pressed(ImGuiKey_G))
    init_mcl_gaussian_();
  if (key_pressed(ImGuiKey_K))
    teleport_robot_();

  handle_teleop_speed_keys_();
  const TeleopAxes axes = read_teleop_axes();
  if (!axes.active()) {
    teleop_active_ = false;
    teleop_accum_ = 0.0;
    return;
  }

  const double dist = axes.linear * manual_dist_;
  const double dtheta = axes.angular * manual_dtheta_;
  if (!teleop_active_) {
    step_once_(dist, dtheta);
    teleop_active_ = true;
    teleop_accum_ = 0.0;
    return;
  }

  step_periodic_(teleop_accum_, teleop_period_, dist, dtheta);
}

void SimView::handle_teleop_speed_keys_() {
  if (key_pressed(ImGuiKey_Q)) {
    scale_step(manual_dist_, kSpeedScaleUp, kManualDistMax);
    scale_step(manual_dtheta_, kSpeedScaleUp, kManualDthetaMax);
  }
  if (key_pressed(ImGuiKey_Z)) {
    scale_step(manual_dist_, kSpeedScaleDown, kManualDistMax);
    scale_step(manual_dtheta_, kSpeedScaleDown, kManualDthetaMax);
  }
  if (key_pressed(ImGuiKey_X))
    scale_step(manual_dist_, kSpeedScaleDown, kManualDistMax);
  if (key_pressed(ImGuiKey_E))
    scale_step(manual_dtheta_, kSpeedScaleUp, kManualDthetaMax);
  if (key_pressed(ImGuiKey_C))
    scale_step(manual_dtheta_, kSpeedScaleDown, kManualDthetaMax);
}

void SimView::step_periodic_(double &accum, double period, double dist,
                             double dtheta) {
  accum += ImGui::GetIO().DeltaTime;
  int step_count = 0;
  while (accum >= period && step_count < kMaxStepsPerFrame) {
    step_once_(dist, dtheta);
    accum -= period;
    ++step_count;
  }
}

void SimView::step_once_(double dist, double dtheta) {
  Timer total_timer;
  Timer section_timer;
  double predict_ms = 0.0;
  double measure_ms = 0.0;
  double observe_ms = 0.0;

  total_timer.start();
  sim_.step(dist, dtheta);

  section_timer.start();
  active_predict_(dist, dtheta);
  predict_ms = section_timer.stop_ms();

  if (do_update_) {
    section_timer.start();
    const std::vector<Observation> observations = sim_.measure();
    measure_ms = section_timer.stop_ms();

    section_timer.start();
    active_observe_(observations);
    observe_ms = section_timer.stop_ms();
  }
  const double total_ms = total_timer.stop_ms();
  append_performance_(predict_ms, measure_ms, observe_ms, total_ms);

  update_estimate_trajectory_();
  ++mcl_step_;
  append_mcl_history_();
}

void SimView::render_config_() {
  ImGui::TextUnformatted("Config");

  ImGui::SeparatorText("Motion noise");
  slider_double("sigma_v", &config_.sigma_v, sim_config::kSigmaMin,
                sim_config::kSigmaMax, "%.4f");
  slider_double("sigma_w", &config_.sigma_w, sim_config::kSigmaMin,
                sim_config::kSigmaMax, "%.4f");

  ImGui::SeparatorText("Sensor");
  slider_double("max_range", &config_.max_range, sim_config::kMaxRangeMin,
                sim_config::kMaxRangeMax, "%.2f");
  slider_double("fov_half", &config_.fov_half, sim_config::kFovHalfMin,
                sim_config::kFovHalfMax, "%.3f");
  slider_double("sigma_r", &config_.sigma_r, sim_config::kSigmaMin,
                sim_config::kSigmaMax, "%.4f");
  slider_double("sigma_phi", &config_.sigma_phi, sim_config::kSigmaMin,
                sim_config::kSigmaMax, "%.4f");

  ImGui::SeparatorText("Landmarks");
  ImGui::SliderInt("landmark_count", &config_.landmark_count,
                   sim_config::kLandmarkCountMin,
                   sim_config::kLandmarkCountMax);
  slider_range("landmark_min_x", &config_.landmark_min_x, "landmark_max_x",
               &config_.landmark_max_x, sim_config::kLandmarkRangeMin,
               sim_config::kLandmarkRangeMax);
  slider_range("landmark_min_y", &config_.landmark_min_y, "landmark_max_y",
               &config_.landmark_max_y, sim_config::kLandmarkRangeMin,
               sim_config::kLandmarkRangeMax);

  ImGui::SeparatorText("Particle filter");
  ImGui::Text("Mode: %s", mode_label_());
  if (ImGui::RadioButton("MCL", !using_openmp_()))
    switch_mode_(MclMode::Serial);
  ImGui::SameLine();
  if (ImGui::RadioButton("MCL_OMP", using_openmp_()))
    switch_mode_(MclMode::OpenMP);

  ImGui::SliderInt("target particles", &particle_count_, kParticleCountMin,
                   kParticleCountMax);
  ImGui::Text("Active M: %d", active_size_());
  ImGui::Text("Effective N: %.1f", active_effective_n_());
  ImGui::Text("Resamples: %d", active_resample_count_());
  if (using_openmp_()) {
    if (ImGui::SliderInt("OpenMP threads", &omp_thread_count_, 1,
                         omp_thread_limit_)) {
      omp_thread_count_ = std::clamp(omp_thread_count_, 1, omp_thread_limit_);
      omp_set_num_threads(omp_thread_count_);
    }
    ImGui::Text("Thread limit: %d", omp_thread_limit_);
  }

  if (ImGui::Button("Apply & Reset"))
    reset_();
}

void SimView::render_control_() {
  ImGui::TextUnformatted("Control");
  ImGui::Checkbox("Paused", &paused_);
  ImGui::Checkbox("MCL update", &do_update_);
  slider_double("auto_dist", &auto_dist_, -0.5, 0.5, "%.3f");
  slider_double("auto_dtheta", &auto_dtheta_, -0.3, 0.3, "%.3f");
  slider_double("teleop_dist", &manual_dist_, 0.001, 1.0, "%.3f");
  slider_double("teleop_dtheta", &manual_dtheta_, 0.001, 0.8, "%.3f");

  if (ImGui::Button("Reset sim"))
    reset_();
  if (ImGui::Button("Uniform particles"))
    init_mcl_uniform_();
  if (ImGui::Button("Gaussian particles"))
    init_mcl_gaussian_();
  if (ImGui::Button("Kidnap +5m"))
    teleport_robot_();

  ImGui::Spacing();
  ImGui::TextUnformatted("Keys");
  ImGui::TextUnformatted("W/S move, A/D turn");
  ImGui::TextUnformatted("arrow keys and I/J/L also move/turn");
  ImGui::TextUnformatted("Q/Z speed, X linear down, E/C angular");
  ImGui::TextUnformatted("Space pause, R uniform, G gaussian, K kidnap");

  ImGui::Text("True landmarks: %d",
              static_cast<int>(sim_.true_landmarks.size()));
  ImGui::Text("Known map: %d", static_cast<int>(active_known_map_size_()));
}

void SimView::render_space_() {
  const Bounds bounds = using_openmp_()
                            ? compute_world_bounds(sim_, estimate_trajectory_,
                                                   mcl_omp_)
                            : compute_world_bounds(sim_, estimate_trajectory_,
                                                   mcl_);

  if (!ImPlot::BeginPlot("World", ImVec2(kWorldPlotSize, kWorldPlotSize),
                         ImPlotFlags_Equal))
    return;

  ImPlot::SetupAxes("x", "y");
  ImPlot::SetupAxesLimits(bounds.min_x, bounds.max_x, bounds.min_y,
                          bounds.max_y, ImPlotCond_Always);
  ImPlot::SetupFinish();

  if (ImPlot::IsPlotHovered()) {
    const ImPlotPoint mouse = ImPlot::GetPlotMousePos();
    bool map_changed = false;
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
      sim_.add_true_landmark(mouse.x, mouse.y);
      map_changed = true;
    }
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      map_changed = sim_.remove_true_landmark_near(mouse.x, mouse.y, 0.6);
    if (map_changed)
      sync_mcl_known_map_();
  }

  ImDrawList *draw = ImPlot::GetPlotDrawList();
  draw_fov(draw, sim_.true_pose, sim_.sensor);
  draw_trajectory(draw, sim_.trajectory_true, rgba(28, 91, 168, 210), 2.0f,
                  false);
  draw_trajectory(draw, estimate_trajectory_, rgba(226, 121, 38, 220), 2.0f,
                  true);

  reserve_particle_buffers_();
  particle_x_.clear();
  particle_y_.clear();
  for (const Particle &p : active_particles_()) {
    particle_x_.push_back(p.x);
    particle_y_.push_back(p.y);
  }
  if (!particle_x_.empty()) {
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 2.0f,
                               ImVec4(0.90f, 0.45f, 0.12f, 0.45f), 0.0f,
                               ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImPlot::PlotScatter("particles", particle_x_.data(), particle_y_.data(),
                        static_cast<int>(particle_x_.size()));
  }

  std::vector<double> landmark_x;
  std::vector<double> landmark_y;
  landmark_x.reserve(sim_.true_landmarks.size());
  landmark_y.reserve(sim_.true_landmarks.size());
  for (const Eigen::Vector2d &lm : sim_.true_landmarks) {
    landmark_x.push_back(lm.x());
    landmark_y.push_back(lm.y());
  }
  if (!landmark_x.empty()) {
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 6.0f,
                               ImVec4(0.02f, 0.34f, 0.28f, 1.0f), 1.0f,
                               ImVec4(0.01f, 0.18f, 0.15f, 1.0f));
    ImPlot::PlotScatter("landmarks", landmark_x.data(), landmark_y.data(),
                        static_cast<int>(landmark_x.size()));
  }

  const Pose2D mean = active_mean_pose_();
  draw_pose_arrow(draw, sim_.true_pose, rgba(30, 89, 174, 230),
                  rgba(13, 38, 76, 255));
  draw->AddCircleFilled(plot_to_pixels(Eigen::Vector2d(mean.x, mean.y)), 4.0f,
                        rgba(226, 121, 38, 245), 24);
  draw_pose_arrow(draw, mean, rgba(226, 121, 38, 220),
                  rgba(95, 51, 13, 255));

  ImPlot::EndPlot();
}

void SimView::render_effective_n_() {
  ImGui::TextUnformatted("Effective N");
  if (!ImPlot::BeginPlot("Effective N", ImVec2(-1, kSmallPlotH)))
    return;

  ImPlot::SetupAxes("step", "N_eff");
  const double xmax =
      history_step_.empty() ? 10.0 : std::max(10.0, history_step_.back());
  const double ymax = std::max(1.0, static_cast<double>(active_size_()));
  ImPlot::SetupAxesLimits(0.0, xmax, 0.0, ymax, ImPlotCond_Always);
  if (!effective_n_history_.empty()) {
    ImPlot::PlotLine("N_eff", history_step_.data(),
                     effective_n_history_.data(),
                     static_cast<int>(effective_n_history_.size()));
    const double threshold = 0.5 * static_cast<double>(active_size_());
    ImPlot::SetNextLineStyle(ImVec4(0.65f, 0.12f, 0.14f, 1.0f), 1.0f);
    ImPlot::PlotInfLines("M/2", &threshold, 1,
                         ImPlotInfLinesFlags_Horizontal);
  }
  ImPlot::EndPlot();
}

void SimView::render_pose_error_() {
  ImGui::TextUnformatted("Pose error");
  if (!ImPlot::BeginPlot("Pose error", ImVec2(-1, kSmallPlotH)))
    return;

  ImPlot::SetupAxes("step", "position error");
  const double xmax =
      history_step_.empty() ? 10.0 : std::max(10.0, history_step_.back());
  ImPlot::SetupAxisLimits(ImAxis_X1, 0.0, xmax, ImPlotCond_Always);
  if (!pose_error_history_.empty()) {
    ImPlot::PlotLine("error", history_step_.data(), pose_error_history_.data(),
                     static_cast<int>(pose_error_history_.size()));
  }
  ImPlot::EndPlot();
}

void SimView::render_performance_() {
  ImGui::Text("Performance (%s)", mode_label_());
  ImGui::SameLine();
  if (ImGui::Button("Clear timing"))
    clear_all_performance_();

  auto mean = [](const std::vector<double> &values) {
    if (values.empty())
      return 0.0;
    return std::accumulate(values.begin(), values.end(), 0.0) /
           static_cast<double>(values.size());
  };
  auto latest = [](const std::vector<double> &values) {
    return values.empty() ? 0.0 : values.back();
  };
  auto p95 = [](const std::vector<double> &values) {
    if (values.empty())
      return 0.0;
    std::vector<double> sorted(values.begin(), values.end());
    std::sort(sorted.begin(), sorted.end());
    const std::size_t idx = static_cast<std::size_t>(
        std::floor(0.95 * static_cast<double>(sorted.size() - 1)));
    return sorted[idx];
  };

  if (ImGui::BeginTable("perf_summary", 7,
                        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
    ImGui::TableSetupColumn("mode");
    ImGui::TableSetupColumn("n");
    ImGui::TableSetupColumn("latest");
    ImGui::TableSetupColumn("mean");
    ImGui::TableSetupColumn("p95");
    ImGui::TableSetupColumn("predict");
    ImGui::TableSetupColumn("update");
    ImGui::TableHeadersRow();

    auto row = [&](const char *label, const PerformanceHistory &perf) {
      const double update_mean = mean(perf.measure_ms) + mean(perf.observe_ms);
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::TextUnformatted(label);
      ImGui::TableSetColumnIndex(1);
      ImGui::Text("%d", static_cast<int>(perf.total_ms.size()));
      ImGui::TableSetColumnIndex(2);
      ImGui::Text("%.3f ms", latest(perf.total_ms));
      ImGui::TableSetColumnIndex(3);
      ImGui::Text("%.3f ms", mean(perf.total_ms));
      ImGui::TableSetColumnIndex(4);
      ImGui::Text("%.3f ms", p95(perf.total_ms));
      ImGui::TableSetColumnIndex(5);
      ImGui::Text("%.3f ms", mean(perf.predict_ms));
      ImGui::TableSetColumnIndex(6);
      ImGui::Text("%.3f ms", update_mean);
    };
    row("MCL", serial_performance_);
    row("MCL_OMP", openmp_performance_);
    ImGui::EndTable();
  }

  const PerformanceHistory &perf = active_performance_();
  if (perf.sample.empty()) {
    ImGui::TextUnformatted("No timing samples yet.");
    return;
  }

  if (!ImPlot::BeginPlot("Step timing", ImVec2(-1, 165.0f)))
    return;

  const double xmax = std::max(10.0, perf.sample.back());
  const double ymax =
      std::max(1.0, *std::max_element(perf.total_ms.begin(),
                                      perf.total_ms.end()) *
                        1.15);
  ImPlot::SetupAxes("sample", "ms");
  ImPlot::SetupAxesLimits(0.0, xmax, 0.0, ymax, ImPlotCond_Always);
  ImPlot::PlotLine("predict", perf.sample.data(), perf.predict_ms.data(),
                   static_cast<int>(perf.sample.size()));
  ImPlot::PlotLine("measure", perf.sample.data(), perf.measure_ms.data(),
                   static_cast<int>(perf.sample.size()));
  ImPlot::PlotLine("update", perf.sample.data(), perf.observe_ms.data(),
                   static_cast<int>(perf.sample.size()));
  ImPlot::PlotLine("total", perf.sample.data(), perf.total_ms.data(),
                   static_cast<int>(perf.sample.size()));
  ImPlot::EndPlot();
}
