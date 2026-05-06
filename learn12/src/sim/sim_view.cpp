#include "sim_view.hpp"

#include "../geom.hpp"
#include "sim_config.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <Eigen/Dense>

#include <algorithm>
#include <cmath>
#include <vector>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kEllipse95 = 2.448;
constexpr int kMaxStepsPerFrame = 4;
constexpr float kWorldPanelW = 620.0f;
constexpr float kWorldPanelH = 630.0f;
constexpr float kWorldPlotSize = 600.0f;
constexpr float kSmallPanelH = 300.0f;
constexpr float kPMatrixPanelW = 410.0f;
constexpr float kPMatrixPlotW = 390.0f;
constexpr float kPValuesPanelW = 520.0f;
constexpr float kPValuesTableW = 500.0f;
constexpr float kSmallPlotH = 260.0f;
constexpr double kManualStepMin = 0.001;
constexpr double kManualDistMax = 1.0;
constexpr double kManualDthetaMax = 0.8;
constexpr double kSpeedScaleUp = 1.1;
constexpr double kSpeedScaleDown = 0.9;

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

TeleopAxes read_teleop_axes() {
  TeleopAxes axes;
  if (key_down(ImGuiKey_K))
    return axes;

  const bool forward = key_down(ImGuiKey_U) || key_down(ImGuiKey_I) ||
                       key_down(ImGuiKey_O) || key_down(ImGuiKey_UpArrow);
  const bool backward = key_down(ImGuiKey_M) || key_down(ImGuiKey_Comma) ||
                        key_down(ImGuiKey_Period) ||
                        key_down(ImGuiKey_DownArrow);
  const bool left = key_down(ImGuiKey_U) || key_down(ImGuiKey_J) ||
                    key_down(ImGuiKey_Period) || key_down(ImGuiKey_LeftArrow);
  const bool right =
      key_down(ImGuiKey_O) || key_down(ImGuiKey_L) || key_down(ImGuiKey_M) ||
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

void draw_cov_ellipse(ImDrawList *draw, const Eigen::Vector2d &mean,
                      const Eigen::Matrix2d &cov, ImU32 color,
                      float thickness = 1.5f) {
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> solver(cov);
  if (solver.info() != Eigen::Success)
    return;

  const Eigen::Vector2d evals = solver.eigenvalues().cwiseMax(0.0);
  const Eigen::Matrix2d evecs = solver.eigenvectors();

  std::vector<ImVec2> points;
  points.reserve(72);
  for (int i = 0; i < 72; ++i) {
    const double t = (2.0 * kPi * static_cast<double>(i)) / 72.0;
    Eigen::Vector2d unit(std::cos(t) * std::sqrt(evals.x()),
                         std::sin(t) * std::sqrt(evals.y()));
    const Eigen::Vector2d p = mean + kEllipse95 * (evecs * unit);
    points.push_back(plot_to_pixels(p));
  }

  draw->AddPolyline(points.data(), static_cast<int>(points.size()), color,
                    ImDrawFlags_Closed, thickness);
}

void draw_robot_arrow(ImDrawList *draw, const Pose2D &pose) {
  const double s = 0.35;
  const Eigen::Vector2d forward(std::cos(pose.theta), std::sin(pose.theta));
  const Eigen::Vector2d left(-std::sin(pose.theta), std::cos(pose.theta));
  const Eigen::Vector2d center(pose.x, pose.y);
  const Eigen::Vector2d tip = center + s * forward;
  const Eigen::Vector2d base = center - 0.45 * s * forward;
  const Eigen::Vector2d p1 = base + 0.55 * s * left;
  const Eigen::Vector2d p2 = base - 0.55 * s * left;

  draw->AddTriangleFilled(plot_to_pixels(tip), plot_to_pixels(p1),
                          plot_to_pixels(p2), rgba(30, 89, 174, 230));
  draw->AddTriangle(plot_to_pixels(tip), plot_to_pixels(p1), plot_to_pixels(p2),
                    rgba(13, 38, 76, 255), 1.5f);
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

Bounds compute_world_bounds(const Sim2D &sim) {
  Bounds bounds;
  bounds.add(sim.true_pose.x - sim.sensor.max_range,
             sim.true_pose.y - sim.sensor.max_range);
  bounds.add(sim.true_pose.x + sim.sensor.max_range,
             sim.true_pose.y + sim.sensor.max_range);

  for (const Eigen::Vector2d &lm : sim.true_landmarks)
    bounds.add(lm.x(), lm.y());
  for (const Pose2D &pose : sim.trajectory_true)
    bounds.add(pose.x, pose.y);
  for (const Pose2D &pose : sim.trajectory_est)
    bounds.add(pose.x, pose.y);

  for (int i = 0; i < sim.ekf.get_landmark_count(); ++i) {
    if (sim.ekf.x.size() > LY(i))
      bounds.add(sim.ekf.x(LX(i)), sim.ekf.x(LY(i)));
  }

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

SimView::SimView(GLFWwindow *win) : window_(win) {
  sim_config::load(config_);
  reset_();
}

SimView::~SimView() {
  sim_config::sanitize(config_);
  sim_config::save(config_);
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
  ImGui::Begin("learn12 SimView", nullptr,
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

  ImGui::BeginChild("pmatrix", ImVec2(kPMatrixPanelW, kSmallPanelH),
                    ImGuiChildFlags_Borders);
  render_pmatrix_();
  ImGui::EndChild();

  ImGui::SameLine();
  ImGui::BeginChild("pvalues", ImVec2(kPValuesPanelW, kSmallPanelH),
                    ImGuiChildFlags_Borders);
  render_pvalues_();
  ImGui::EndChild();
  ImGui::EndChild();

  ImGui::End();
}

void SimView::reset_() {
  sim_config::sanitize(config_);
  sim_config::save(config_);
  sim_.init(config_);

  auto_accum_ = 0.0;
  teleop_active_ = false;
  teleop_accum_ = 0.0;
}

void SimView::handle_keyboard_() {
  if (ImGui::GetIO().WantTextInput)
    return;

  if (key_pressed(ImGuiKey_Space))
    paused_ = !paused_;
  if (key_pressed(ImGuiKey_R))
    reset_();

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
  if (key_pressed(ImGuiKey_W))
    scale_step(manual_dist_, kSpeedScaleUp, kManualDistMax);
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
  sim_.step(dist, dtheta);
  if (do_update_)
    sim_.process_observations();
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

  if (ImGui::Button("Apply & Reset"))
    reset_();
}

void SimView::render_control_() {
  ImGui::TextUnformatted("Control");
  ImGui::Checkbox("Paused", &paused_);
  ImGui::Checkbox("EKF update", &do_update_);
  slider_double("auto_dist", &auto_dist_, -0.5, 0.5, "%.3f");
  slider_double("auto_dtheta", &auto_dtheta_, -0.3, 0.3, "%.3f");
  slider_double("teleop_dist", &manual_dist_, 0.001, 1.0, "%.3f");
  slider_double("teleop_dtheta", &manual_dtheta_, 0.001, 0.8, "%.3f");

  if (ImGui::Button("Reset"))
    reset_();

  ImGui::Spacing();
  ImGui::TextUnformatted("ROS teleop keys");
  ImGui::TextUnformatted("  u    i    o");
  ImGui::TextUnformatted("  j    k    l");
  ImGui::TextUnformatted("  m    ,    .");
  ImGui::TextUnformatted("arrow keys also move/turn");
  ImGui::TextUnformatted("q/z all, w/x linear, e/c angular");
  ImGui::TextUnformatted("space pause, r reset");

  ImGui::Text("True landmarks: %d",
              static_cast<int>(sim_.true_landmarks.size()));
  ImGui::Text("EKF landmarks: %d", sim_.ekf.get_landmark_count());
}

void SimView::render_space_() {
  const Bounds bounds = compute_world_bounds(sim_);

  if (!ImPlot::BeginPlot("World", ImVec2(kWorldPlotSize, kWorldPlotSize),
                         ImPlotFlags_Equal))
    return;

  ImPlot::SetupAxes("x", "y");
  ImPlot::SetupAxesLimits(bounds.min_x, bounds.max_x, bounds.min_y,
                          bounds.max_y, ImPlotCond_Always);
  ImPlot::SetupFinish();

  if (ImPlot::IsPlotHovered()) {
    const ImPlotPoint mouse = ImPlot::GetPlotMousePos();
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
      sim_.add_true_landmark(mouse.x, mouse.y);
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      sim_.remove_true_landmark_near(mouse.x, mouse.y, 0.6);
  }

  ImDrawList *draw = ImPlot::GetPlotDrawList();
  draw_fov(draw, sim_.true_pose, sim_.sensor);
  draw_trajectory(draw, sim_.trajectory_true, rgba(28, 91, 168, 210), 2.0f,
                  false);
  draw_trajectory(draw, sim_.trajectory_est, rgba(226, 121, 38, 220), 2.0f,
                  true);

  std::vector<double> unseen_x;
  std::vector<double> unseen_y;
  std::vector<double> seen_x;
  std::vector<double> seen_y;
  for (std::size_t i = 0; i < sim_.true_landmarks.size(); ++i) {
    const Eigen::Vector2d &lm = sim_.true_landmarks[i];
    if (i < sim_.true_to_ekf_idx.size() && sim_.true_to_ekf_idx[i] >= 0) {
      seen_x.push_back(lm.x());
      seen_y.push_back(lm.y());
    } else {
      unseen_x.push_back(lm.x());
      unseen_y.push_back(lm.y());
    }
  }

  if (!unseen_x.empty()) {
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 5.0f,
                               ImVec4(0.55f, 0.56f, 0.58f, 1.0f), 1.0f,
                               ImVec4(0.40f, 0.41f, 0.43f, 1.0f));
    ImPlot::PlotScatter("true unseen", unseen_x.data(), unseen_y.data(),
                        static_cast<int>(unseen_x.size()));
  }
  if (!seen_x.empty()) {
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 6.0f,
                               ImVec4(0.02f, 0.34f, 0.28f, 1.0f), 1.0f,
                               ImVec4(0.01f, 0.18f, 0.15f, 1.0f));
    ImPlot::PlotScatter("true seen", seen_x.data(), seen_y.data(),
                        static_cast<int>(seen_x.size()));
  }

  std::vector<double> est_x;
  std::vector<double> est_y;
  for (int i = 0; i < sim_.ekf.get_landmark_count(); ++i) {
    if (sim_.ekf.x.size() <= LY(i))
      continue;
    const Eigen::Vector2d mean(sim_.ekf.x(LX(i)), sim_.ekf.x(LY(i)));
    est_x.push_back(mean.x());
    est_y.push_back(mean.y());
    if (sim_.ekf.P.rows() > LY(i)) {
      const Eigen::Matrix2d cov = sim_.ekf.P.block<2, 2>(LX(i), LX(i));
      draw_cov_ellipse(draw, mean, cov, rgba(35, 99, 178, 170), 1.2f);
    }
  }
  if (!est_x.empty()) {
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 8.0f,
                               ImVec4(0.0f, 0.0f, 0.0f, 0.0f), 1.8f,
                               ImVec4(0.12f, 0.36f, 0.76f, 1.0f));
    ImPlot::PlotScatter("estimated landmarks", est_x.data(), est_y.data(),
                        static_cast<int>(est_x.size()));
  }

  draw_robot_arrow(draw, sim_.true_pose);
  if (sim_.ekf.x.size() >= 3) {
    const Eigen::Vector2d robot_mean(sim_.ekf.x(RX), sim_.ekf.x(RY));
    draw->AddCircleFilled(plot_to_pixels(robot_mean), 5.0f,
                          rgba(226, 121, 38, 245), 24);
    draw->AddCircle(plot_to_pixels(robot_mean), 5.0f, rgba(95, 51, 13, 255),
                    24, 1.5f);
    draw_cov_ellipse(draw, robot_mean, sim_.ekf.P.block<2, 2>(0, 0),
                     rgba(226, 121, 38, 190), 1.6f);
  }

  ImPlot::EndPlot();
}

void SimView::render_pmatrix_() {
  ImGui::TextUnformatted("P Matrix");
  const int n = static_cast<int>(sim_.ekf.P.rows());
  if (n == 0)
    return;

  std::vector<double> values(static_cast<std::size_t>(n * n));
  double max_abs = 0.0;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      const double v = sim_.ekf.P(r, c);
      values[static_cast<std::size_t>(r * n + c)] = v;
      max_abs = std::max(max_abs, std::abs(v));
    }
  }
  max_abs = std::max(max_abs, 1e-12);

  ImPlot::PushColormap(ImPlotColormap_RdBu);
  if (ImPlot::BeginPlot("P heatmap",
                        ImVec2(kPMatrixPlotW, kSmallPlotH))) {
    ImPlot::SetupAxes("col", "row", ImPlotAxisFlags_NoTickLabels,
                      ImPlotAxisFlags_NoTickLabels);
    ImPlot::SetupAxesLimits(0.0, static_cast<double>(n), 0.0,
                            static_cast<double>(n), ImPlotCond_Always);
    ImPlot::PlotHeatmap("P", values.data(), n, n, -max_abs, max_abs, nullptr,
                        ImPlotPoint(0, 0), ImPlotPoint(n, n));
    ImPlot::EndPlot();
  }
  ImPlot::PopColormap();
}

void SimView::render_pvalues_() {
  ImGui::TextUnformatted("P Values");
  const int n = static_cast<int>(sim_.ekf.P.rows());
  if (n == 0)
    return;

  const ImGuiTableFlags flags =
      ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
      ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY |
      ImGuiTableFlags_SizingFixedFit;
  if (ImGui::BeginTable("P values table", n + 1, flags,
                        ImVec2(kPValuesTableW, kSmallPlotH))) {
    ImGui::TableSetupScrollFreeze(1, 1);
    ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
    ImGui::TableSetColumnIndex(0);
    ImGui::TextUnformatted("r\\c");
    for (int c = 0; c < n; ++c) {
      ImGui::TableSetColumnIndex(c + 1);
      ImGui::Text("c%d", c);
    }

    for (int r = 0; r < n; ++r) {
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Text("r%d", r);
      for (int c = 0; c < n; ++c) {
        ImGui::TableSetColumnIndex(c + 1);
        ImGui::Text("%.3g", sim_.ekf.P(r, c));
      }
    }
    ImGui::EndTable();
  }
}
