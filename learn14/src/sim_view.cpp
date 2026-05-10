#include "sim_view.hpp"

#include "geom.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "sim/sim_config.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <random>
#include <vector>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kStepDt = 0.05;
constexpr double kInitialStd = 0.1;
constexpr double kDeleteRadius = 0.5;

constexpr ImU32 COLOR_TRUTH = IM_COL32(120, 120, 120, 255);
constexpr ImU32 COLOR_MEAN_LM = IM_COL32(80, 130, 230, 255);
constexpr ImU32 COLOR_BEST_LM = IM_COL32(0, 220, 210, 255);
constexpr ImU32 COLOR_PARTICLES = IM_COL32(255, 214, 76, 210);
constexpr ImU32 COLOR_MEAN_POSE = IM_COL32(60, 200, 90, 255);
constexpr ImU32 COLOR_TRUE_POSE = IM_COL32(220, 60, 60, 255);
constexpr ImU32 COLOR_SEL_LM = IM_COL32(240, 200, 60, 255);
constexpr ImU32 COLOR_SEL_POSE = IM_COL32(240, 140, 40, 255);
constexpr ImU32 COLOR_FOV_FILL = IM_COL32(70, 150, 240, 34);
constexpr ImU32 COLOR_FOV_LINE = IM_COL32(80, 165, 255, 155);

bool key_down(ImGuiKey key) { return ImGui::IsKeyDown(key); }

bool key_pressed(ImGuiKey key) { return ImGui::IsKeyPressed(key, false); }

bool slider_double(const char *label, double *value, double min_value,
                   double max_value, const char *format = "%.3f") {
  return ImGui::SliderScalar(label, ImGuiDataType_Double, value, &min_value,
                             &max_value, format);
}

bool active_landmark(const Eigen::Vector2d &lm) {
  return std::isfinite(lm.x()) && std::isfinite(lm.y());
}

ImVec4 color_vec(ImU32 color) { return ImGui::ColorConvertU32ToFloat4(color); }

Pose2D particle_pose(const Particle &p) {
  Pose2D pose;
  pose.x = p.x;
  pose.y = p.y;
  pose.theta = p.theta;
  return pose;
}

void plot_scatter(const char *label, const std::vector<double> &xs,
                  const std::vector<double> &ys, ImPlotMarker marker,
                  float size, ImU32 color, float outline_weight = 1.0f) {
  if (xs.empty())
    return;

  const ImVec4 c = color_vec(color);
  const ImVec4 outline = outline_weight > 0.0f ? c : ImVec4(0, 0, 0, 0);
  ImPlot::SetNextMarkerStyle(marker, size, c, outline_weight, outline);
  ImPlot::PlotScatter(label, xs.data(), ys.data(), static_cast<int>(xs.size()));
}

void plot_point(const char *label, double x, double y, ImPlotMarker marker,
                float size, ImU32 color) {
  const double xs[1] = {x};
  const double ys[1] = {y};
  const ImVec4 c = color_vec(color);
  ImPlot::SetNextMarkerStyle(marker, size, c, 1.0f, c);
  ImPlot::PlotScatter(label, xs, ys, 1);
}

struct Bounds {
  double min_x = -5.0;
  double max_x = 5.0;
  double min_y = -5.0;
  double max_y = 5.0;

  void add(double x, double y) {
    if (!std::isfinite(x) || !std::isfinite(y))
      return;
    min_x = std::min(min_x, x);
    max_x = std::max(max_x, x);
    min_y = std::min(min_y, y);
    max_y = std::max(max_y, y);
  }

  void square_with_padding(double pad) {
    min_x -= pad;
    max_x += pad;
    min_y -= pad;
    max_y += pad;

    const double cx = 0.5 * (min_x + max_x);
    const double cy = 0.5 * (min_y + max_y);
    const double half =
        0.5 * std::max(std::max(max_x - min_x, max_y - min_y), 1.0);
    min_x = cx - half;
    max_x = cx + half;
    min_y = cy - half;
    max_y = cy + half;
  }
};
} // namespace

SimView::SimView() : rng(std::random_device{}()) {
  load_config();
  hist_pose_rmse.assign(HIST_LEN, 0.0f);
  hist_lm_rmse.assign(HIST_LEN, 0.0f);
  hist_n_eff.assign(HIST_LEN, 0.0f);
  filter = FastSLAM(sigma_v, sigma_w, sigma_r, sigma_phi, 42);
}

SimView::~SimView() {
  if (ui_initialized) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
  }
  if (window != nullptr)
    glfwDestroyWindow(window);
  if (glfw_initialized)
    glfwTerminate();
}

bool SimView::init(int window_width, int window_height) {
  if (!glfwInit()) {
    std::fprintf(stderr, "glfwInit failed\n");
    return false;
  }
  glfw_initialized = true;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(window_width, window_height, "FastSLAM SimView",
                            nullptr, nullptr);
  if (window == nullptr) {
    std::fprintf(stderr, "glfwCreateWindow failed\n");
    return false;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::StyleColorsDark();
  const bool glfw_backend_initialized =
      ImGui_ImplGlfw_InitForOpenGL(window, true);
  const bool opengl_backend_initialized = ImGui_ImplOpenGL3_Init("#version 330");
  if (!glfw_backend_initialized || !opengl_backend_initialized) {
    std::fprintf(stderr, "ImGui backend init failed\n");
    if (opengl_backend_initialized)
      ImGui_ImplOpenGL3_Shutdown();
    if (glfw_backend_initialized)
      ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    return false;
  }
  ui_initialized = true;

  restart_from_config();
  return true;
}

void SimView::run() {
  if (window == nullptr)
    return;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (paused) {
      frame_dt = 0.0;
      step_dist = 0.0;
      step_dtheta = 0.0;
      handle_input();
    } else {
      step(kStepDt);
    }
    refresh_filter_cache();
    update_history();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(viewport->WorkSize, ImGuiCond_Always);
    ImGui::Begin("learn14 FastSLAM", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoResize);

    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float spacing = ImGui::GetStyle().ItemSpacing.x;
    const float world_w = std::max(420.0f, avail.x * 0.50f);
    const float series_w = std::max(300.0f, avail.x * 0.25f);
    const float info_w =
        std::max(280.0f, avail.x - world_w - series_w - 2.0f * spacing);

    ImGui::BeginChild("world_panel", ImVec2(world_w, 0),
                      ImGuiChildFlags_Borders);
    render_world_panel();
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("timeseries_panel", ImVec2(series_w, 0),
                      ImGuiChildFlags_Borders);
    render_timeseries_panel();
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("info_panel", ImVec2(info_w, 0), ImGuiChildFlags_Borders);
    render_info_panel();
    ImGui::EndChild();

    ImGui::End();

    ImGui::Render();
    int display_w = 0;
    int display_h = 0;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.08f, 0.09f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }
}

void SimView::step(double dt) {
  frame_dt = dt;
  step_dist = 0.0;
  step_dtheta = 0.0;
  handle_input();
  if (paused)
    return;

  filter.predict(step_dist, step_dtheta);
  observation_buffer.clear();
  simulate_observations(observation_buffer);
  filter.observe(observation_buffer);
  last_resampled = filter.last_resampled;
  cache_dirty = true;
}

void SimView::simulate_observations(std::vector<Observation> &obs) const {
  std::normal_distribution<double> r_noise(0.0, sigma_r);
  std::normal_distribution<double> phi_noise(0.0, sigma_phi);
  const double max_range_sq = max_range * max_range;

  for (int j = 0; j < static_cast<int>(landmarks_true.size()); ++j) {
    const Eigen::Vector2d &lm = landmarks_true[j];
    if (!active_landmark(lm))
      continue;

    const double dx = lm.x() - robot_true.x;
    const double dy = lm.y() - robot_true.y;
    const double q = dx * dx + dy * dy;
    if (q > max_range_sq)
      continue;

    double r = std::sqrt(q);
    double phi = wrap(std::atan2(dy, dx) - robot_true.theta);

    if (std::abs(phi) > fov_half)
      continue;

    r = std::max(1e-6, r + r_noise(rng));
    phi = wrap(phi + phi_noise(rng));
    obs.push_back({j, r, phi});
  }
}

void SimView::handle_input() {
  ImGuiIO &io = ImGui::GetIO();
  if (io.WantTextInput)
    return;

  if (key_pressed(ImGuiKey_Space))
    paused = !paused;
  if (key_pressed(ImGuiKey_R)) {
    init_filter_at_true();
    reset_history();
    cache_dirty = true;
  }
  if (key_pressed(ImGuiKey_Y)) {
    restart_from_config();
    cache_dirty = true;
  }
  if (key_pressed(ImGuiKey_X)) {
    std::uniform_real_distribution<double> xy(-5.0, 5.0);
    std::uniform_real_distribution<double> th(-kPi, kPi);
    robot_true.x = xy(rng);
    robot_true.y = xy(rng);
    robot_true.theta = th(rng);
    cache_dirty = true;
  }
  if (key_pressed(ImGuiKey_N) && filter.size() > 0)
    selected_particle = (selected_particle + 1) % filter.size();
  if (key_pressed(ImGuiKey_P)) {
    show_particles = !show_particles;
    cache_dirty = true;
    save_config();
  }
  if (key_pressed(ImGuiKey_V)) {
    show_fov = !show_fov;
    save_config();
  }
  if (key_pressed(ImGuiKey_E)) {
    show_ellipses = !show_ellipses;
    save_config();
  }
  if (key_pressed(ImGuiKey_G)) {
    show_mean_landmarks = !show_mean_landmarks;
    save_config();
  }
  if (key_pressed(ImGuiKey_B)) {
    show_best_particle_map = !show_best_particle_map;
    save_config();
  }

  if (paused || frame_dt <= 0.0)
    return;

  const double forward =
      ((key_down(ImGuiKey_W) || key_down(ImGuiKey_U) ||
        key_down(ImGuiKey_I) || key_down(ImGuiKey_O))
           ? 1.0
           : 0.0) -
      ((key_down(ImGuiKey_S) || key_down(ImGuiKey_M) ||
        key_down(ImGuiKey_Comma) || key_down(ImGuiKey_Period))
           ? 1.0
           : 0.0);
  const double turn =
      ((key_down(ImGuiKey_A) || key_down(ImGuiKey_U) ||
        key_down(ImGuiKey_J) || key_down(ImGuiKey_Period))
           ? 1.0
           : 0.0) -
      ((key_down(ImGuiKey_D) || key_down(ImGuiKey_O) ||
        key_down(ImGuiKey_L) || key_down(ImGuiKey_M))
           ? 1.0
           : 0.0);

  step_dist = forward * linear_speed * frame_dt;
  step_dtheta = turn * angular_speed * frame_dt;

  const double mid = robot_true.theta + 0.5 * step_dtheta;
  robot_true.x += step_dist * std::cos(mid);
  robot_true.y += step_dist * std::sin(mid);
  robot_true.theta = wrap(robot_true.theta + step_dtheta);
}

void SimView::render_world_panel() {
  ImGui::TextUnformatted("World");

  Bounds bounds;
  bounds.add(robot_true.x - max_range, robot_true.y - max_range);
  bounds.add(robot_true.x + max_range, robot_true.y + max_range);
  for (const Eigen::Vector2d &lm : landmarks_true)
    if (active_landmark(lm))
      bounds.add(lm.x(), lm.y());
  if (show_particles) {
    for (std::size_t i = 0; i < particle_plot_x.size(); ++i)
      bounds.add(particle_plot_x[i], particle_plot_y[i]);
  }

  const Pose2D mean = cached_mean_pose;
  bounds.add(mean.x, mean.y);

  const std::vector<Eigen::Vector2d> &means = cached_mean_landmarks;
  for (std::size_t j = 0; j < means.size(); ++j) {
    if (landmark_seen_weight(static_cast<int>(j)) > 0.0)
      bounds.add(means[j].x(), means[j].y());
  }
  if (selected_particle >= 0 && selected_particle < filter.size()) {
    const Particle &p = filter.particles[selected_particle];
    for (const LandmarkEKF &lm : p.landmarks)
      if (lm.seen)
        bounds.add(lm.mu.x(), lm.mu.y());
  }
  if (show_best_particle_map && cached_best_particle >= 0 &&
      cached_best_particle < filter.size()) {
    const Particle &p = filter.particles[cached_best_particle];
    for (const LandmarkEKF &lm : p.landmarks)
      if (lm.seen)
        bounds.add(lm.mu.x(), lm.mu.y());
  }
  bounds.square_with_padding(1.0);

  if (!ImPlot::BeginPlot("World##plot", ImVec2(-1, -1), ImPlotFlags_Equal))
    return;

  ImPlot::SetupAxes("x", "y");
  ImPlot::SetupAxesLimits(bounds.min_x, bounds.max_x, bounds.min_y,
                          bounds.max_y, ImPlotCond_Always);
  ImPlot::SetupFinish();

  if (ImPlot::IsPlotHovered()) {
    const ImPlotPoint mouse = ImPlot::GetPlotMousePos();
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
      landmarks_true.emplace_back(mouse.x, mouse.y);
      cache_dirty = true;
    }
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      delete_landmark_near(mouse.x, mouse.y, kDeleteRadius);
  }

  if (show_fov)
    draw_sensor_fov(robot_true);

  plot_x.clear();
  plot_y.clear();
  plot_x.reserve(landmarks_true.size());
  plot_y.reserve(landmarks_true.size());
  for (const Eigen::Vector2d &lm : landmarks_true) {
    if (!active_landmark(lm))
      continue;
    plot_x.push_back(lm.x());
    plot_y.push_back(lm.y());
  }
  plot_scatter("truth landmarks", plot_x, plot_y, ImPlotMarker_Cross, 6.0f,
               COLOR_TRUTH, 1.5f);

  if (show_mean_landmarks) {
    plot_x.clear();
    plot_y.clear();
    for (int j = 0; j < static_cast<int>(means.size()); ++j) {
      if (landmark_seen_weight(j) <= 0.0)
        continue;
      plot_x.push_back(means[j].x());
      plot_y.push_back(means[j].y());
    }
    plot_scatter("mean landmarks", plot_x, plot_y, ImPlotMarker_Circle, 5.0f,
                 COLOR_MEAN_LM, 1.0f);
  }

  if (show_best_particle_map && cached_best_particle >= 0 &&
      cached_best_particle < filter.size()) {
    const Particle &p = filter.particles[cached_best_particle];
    plot_x.clear();
    plot_y.clear();
    for (const LandmarkEKF &lm : p.landmarks) {
      if (!lm.seen)
        continue;
      plot_x.push_back(lm.mu.x());
      plot_y.push_back(lm.mu.y());
    }
    plot_scatter("best particle map", plot_x, plot_y, ImPlotMarker_Diamond,
                 6.0f, COLOR_BEST_LM, 1.2f);
  }

  if (show_particles) {
    plot_scatter("particles", particle_plot_x, particle_plot_y,
                 ImPlotMarker_Circle, 2.6f,
                 COLOR_PARTICLES, 0.0f);
  }

  plot_point("mean pose", mean.x, mean.y, ImPlotMarker_Circle, 5.0f,
             COLOR_MEAN_POSE);
  ImGui::PushID("mean_arrow");
  draw_robot_arrow(mean, COLOR_MEAN_POSE, 0.45f);
  ImGui::PopID();

  plot_point("true pose", robot_true.x, robot_true.y, ImPlotMarker_Circle, 5.0f,
             COLOR_TRUE_POSE);
  ImGui::PushID("true_arrow");
  draw_robot_arrow(robot_true, COLOR_TRUE_POSE, 0.45f);
  ImGui::PopID();

  if (show_ellipses && selected_particle >= 0 &&
      selected_particle < filter.size()) {
    const Particle &p = filter.particles[selected_particle];

    plot_x.clear();
    plot_y.clear();
    for (const LandmarkEKF &lm : p.landmarks) {
      if (!lm.seen)
        continue;
      plot_x.push_back(lm.mu.x());
      plot_y.push_back(lm.mu.y());
    }
    plot_scatter("selected landmarks", plot_x, plot_y, ImPlotMarker_Cross, 6.0f,
                 COLOR_SEL_LM, 1.5f);

    for (int j = 0; j < static_cast<int>(p.landmarks.size()); ++j) {
      if (!p.landmarks[j].seen)
        continue;
      ImGui::PushID(j);
      draw_covariance_ellipse(p.landmarks[j].mu, p.landmarks[j].sigma,
                              COLOR_SEL_LM);
      ImGui::PopID();
    }
  }

  if (selected_particle >= 0 && selected_particle < filter.size()) {
    const Pose2D p = particle_pose(filter.particles[selected_particle]);
    ImGui::PushID("selected_arrow");
    draw_robot_arrow(p, COLOR_SEL_POSE, 0.5f);
    ImGui::PopID();
  }

  ImPlot::EndPlot();
}

void SimView::render_timeseries_panel() {
  ImGui::TextUnformatted("Timeseries");
  const int count = hist_count == HIST_LEN ? HIST_LEN : hist_count;
  const int offset = hist_count == HIST_LEN ? hist_idx : 0;
  const float spacing_y = ImGui::GetStyle().ItemSpacing.y;
  const float plot_h = std::max(
      120.0f, (ImGui::GetContentRegionAvail().y - 2.0f * spacing_y) / 3.0f);

  if (ImPlot::BeginPlot("Pose RMSE", ImVec2(-1, plot_h))) {
    ImPlot::SetupAxes("frame", "m");
    ImPlot::SetupAxisLimits(ImAxis_X1, 0.0, HIST_LEN, ImPlotCond_Always);
    if (count > 1)
      ImPlot::PlotLine("pose RMSE", hist_pose_rmse.data(), count, 1.0, 0.0, 0,
                       offset);
    ImPlot::EndPlot();
  }

  if (ImPlot::BeginPlot("Landmark RMSE", ImVec2(-1, plot_h))) {
    ImPlot::SetupAxes("frame", "m");
    ImPlot::SetupAxisLimits(ImAxis_X1, 0.0, HIST_LEN, ImPlotCond_Always);
    if (show_mean_landmarks && count > 1)
      ImPlot::PlotLine("landmark RMSE", hist_lm_rmse.data(), count, 1.0, 0.0, 0,
                       offset);
    ImPlot::EndPlot();
  }

  if (ImPlot::BeginPlot("Effective N", ImVec2(-1, plot_h))) {
    ImPlot::SetupAxes("frame", "N_eff");
    ImPlot::SetupAxesLimits(0.0, HIST_LEN, 0.0, std::max(1, M),
                            ImPlotCond_Always);
    if (count > 1)
      ImPlot::PlotLine("N_eff", hist_n_eff.data(), count, 1.0, 0.0, 0, offset);
    ImPlot::EndPlot();
  }
}

void SimView::render_info_panel() {
  ImGui::SeparatorText("FastSLAM");
  ImGui::Text("Particles: M = %d", filter.size());
  ImGui::Text("N_eff:     %.1f / %d", cached_effective_n, filter.size());
  ImGui::Text("Resampled: %s", last_resampled ? "yes" : "no");
  ImGui::Text("Paused:    %s", paused ? "yes" : "no");

  bool config_changed = false;
  bool restart_requested = false;
  bool save_requested = false;
  ImGui::SeparatorText("Config");

  ImGui::SeparatorText("Particles");
  if (ImGui::SliderInt("particles", &M, sim_config::kParticleCountMin,
                       sim_config::kParticleCountMax)) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }

  ImGui::SeparatorText("Control");
  if (slider_double("linear speed", &linear_speed,
                    sim_config::kLinearSpeedMin,
                    sim_config::kLinearSpeedMax, "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("angular speed", &angular_speed,
                    sim_config::kAngularSpeedMin,
                    sim_config::kAngularSpeedMax, "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Noise");
  if (slider_double("sigma_v", &sigma_v, sim_config::kSigmaMin,
                    sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_w", &sigma_w, sim_config::kSigmaMin,
                    sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_r", &sigma_r, sim_config::kSigmaMin,
                    sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_phi", &sigma_phi, sim_config::kSigmaMin,
                    sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Sensor");
  if (slider_double("max_range", &max_range, sim_config::kMaxRangeMin,
                    sim_config::kMaxRangeMax, "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("fov_half", &fov_half, sim_config::kFovHalfMin,
                    sim_config::kFovHalfMax, "%.3f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Landmarks");
  if (ImGui::SliderInt("landmarks", &landmark_count,
                       sim_config::kLandmarkCountMin,
                       sim_config::kLandmarkCountMax)) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }
  if (ImGui::InputInt("map seed", &map_seed)) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }
  if (slider_double("lm min x", &landmark_min_x,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }
  if (slider_double("lm max x", &landmark_max_x,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }
  if (slider_double("lm min y", &landmark_min_y,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }
  if (slider_double("lm max y", &landmark_max_y,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    restart_requested = true;
    save_requested = true;
  }

  ImGui::SeparatorText("Display");
  if (ImGui::Checkbox("show particles", &show_particles)) {
    config_changed = true;
    save_requested = true;
    cache_dirty = true;
  }
  if (ImGui::Checkbox("show FOV", &show_fov)) {
    config_changed = true;
    save_requested = true;
  }
  if (ImGui::Checkbox("show ellipses", &show_ellipses)) {
    config_changed = true;
    save_requested = true;
  }
  if (ImGui::Checkbox("show mean landmarks", &show_mean_landmarks)) {
    config_changed = true;
    save_requested = true;
  }
  if (ImGui::Checkbox("show best particle map", &show_best_particle_map)) {
    config_changed = true;
    save_requested = true;
  }

  if (config_changed) {
    sanitize_config_values();
    sync_filter_config();
  }
  if (restart_requested) {
    restart_from_config();
    refresh_filter_cache();
  } else if (save_requested) {
    save_config();
  }

  if (ImGui::Button("Reset Environment")) {
    restart_from_config();
    refresh_filter_cache();
  }

  ImGui::SeparatorText("Robot");
  ImGui::Text("True pose: (%.2f, %.2f) theta = %.2f rad", robot_true.x,
              robot_true.y, robot_true.theta);
  ImGui::Text("Mean pose: (%.2f, %.2f) theta = %.2f rad", cached_mean_pose.x,
              cached_mean_pose.y, cached_mean_pose.theta);
  ImGui::Text("Pose RMSE: %.3f m", cached_pose_rmse);

  ImGui::SeparatorText("Map");
  ImGui::Text("GT landmarks:   %d", cached_active_landmark_count);
  ImGui::Text("Mean landmarks: %d seen by majority",
              cached_majority_seen_landmark_count);
  ImGui::Text("Landmark RMSE:  %.3f m", cached_landmark_rmse);
  if (cached_best_particle >= 0 && cached_best_particle < filter.size()) {
    const Particle &best = filter.particles[cached_best_particle];
    ImGui::Text("Best particle:  %d weight = %.6f", cached_best_particle,
                best.weight);
  }

  ImGui::SeparatorText("Selected Particle");
  if (selected_particle >= 0 && selected_particle < filter.size()) {
    const Particle &p = filter.particles[selected_particle];
    int seen = 0;
    for (const LandmarkEKF &lm : p.landmarks)
      if (lm.seen)
        ++seen;
    ImGui::Text("Index:   %d / %d", selected_particle, filter.size());
    ImGui::Text("Weight:  %.6f", p.weight);
    ImGui::Text("Pose:    (%.2f, %.2f) theta = %.2f", p.x, p.y, p.theta);
    ImGui::Text("Landmarks seen: %d", seen);
  } else {
    ImGui::TextUnformatted("No selected particle");
  }
  ImGui::TextUnformatted(
      "[N: next | P: particles | V: FOV | E: ellipses | G: mean | B: best]");

  ImGui::SeparatorText("Controls");
  ImGui::TextUnformatted("u i o / j k l / m , .  teleop move");
  ImGui::TextUnformatted("W/A/S/D                  move robot");
  ImGui::TextUnformatted("Space       pause");
  ImGui::TextUnformatted("R           reinit filter");
  ImGui::TextUnformatted("Y           reset environment");
  ImGui::TextUnformatted("X           kidnap robot");
  ImGui::TextUnformatted("Left click  add landmark");
  ImGui::TextUnformatted("Right click delete landmark");
}

void SimView::load_config() {
  SimConfig config;
  sim_config::load(config);

  M = config.particle_count;
  linear_speed = config.linear_speed;
  angular_speed = config.angular_speed;
  sigma_v = config.sigma_v;
  sigma_w = config.sigma_w;
  max_range = config.max_range;
  fov_half = config.fov_half;
  sigma_r = config.sigma_r;
  sigma_phi = config.sigma_phi;
  landmark_count = config.landmark_count;
  map_seed = config.map_seed;
  landmark_min_x = config.landmark_min_x;
  landmark_max_x = config.landmark_max_x;
  landmark_min_y = config.landmark_min_y;
  landmark_max_y = config.landmark_max_y;
  show_particles = config.show_particles;
  show_fov = config.show_fov;
  show_ellipses = config.show_ellipses;
  show_mean_landmarks = config.show_mean_landmarks;
  show_best_particle_map = config.show_best_particle_map;
}

void SimView::save_config() const {
  SimConfig config;
  config.particle_count = M;
  config.linear_speed = linear_speed;
  config.angular_speed = angular_speed;
  config.sigma_v = sigma_v;
  config.sigma_w = sigma_w;
  config.max_range = max_range;
  config.fov_half = fov_half;
  config.sigma_r = sigma_r;
  config.sigma_phi = sigma_phi;
  config.landmark_count = landmark_count;
  config.map_seed = map_seed;
  config.landmark_min_x = landmark_min_x;
  config.landmark_max_x = landmark_max_x;
  config.landmark_min_y = landmark_min_y;
  config.landmark_max_y = landmark_max_y;
  config.show_particles = show_particles;
  config.show_fov = show_fov;
  config.show_ellipses = show_ellipses;
  config.show_mean_landmarks = show_mean_landmarks;
  config.show_best_particle_map = show_best_particle_map;

  sim_config::sanitize(config);
  sim_config::save(config);
}

void SimView::sanitize_config_values() {
  SimConfig config;
  config.particle_count = M;
  config.linear_speed = linear_speed;
  config.angular_speed = angular_speed;
  config.sigma_v = sigma_v;
  config.sigma_w = sigma_w;
  config.max_range = max_range;
  config.fov_half = fov_half;
  config.sigma_r = sigma_r;
  config.sigma_phi = sigma_phi;
  config.landmark_count = landmark_count;
  config.map_seed = map_seed;
  config.landmark_min_x = landmark_min_x;
  config.landmark_max_x = landmark_max_x;
  config.landmark_min_y = landmark_min_y;
  config.landmark_max_y = landmark_max_y;
  config.show_particles = show_particles;
  config.show_fov = show_fov;
  config.show_ellipses = show_ellipses;
  config.show_mean_landmarks = show_mean_landmarks;
  config.show_best_particle_map = show_best_particle_map;

  sim_config::sanitize(config);
  M = config.particle_count;
  linear_speed = config.linear_speed;
  angular_speed = config.angular_speed;
  sigma_v = config.sigma_v;
  sigma_w = config.sigma_w;
  max_range = config.max_range;
  fov_half = config.fov_half;
  sigma_r = config.sigma_r;
  sigma_phi = config.sigma_phi;
  landmark_count = config.landmark_count;
  map_seed = config.map_seed;
  landmark_min_x = config.landmark_min_x;
  landmark_max_x = config.landmark_max_x;
  landmark_min_y = config.landmark_min_y;
  landmark_max_y = config.landmark_max_y;
}

void SimView::sync_filter_config() {
  filter.sigma_v = sigma_v;
  filter.sigma_w = sigma_w;
  filter.sigma_r = sigma_r;
  filter.sigma_phi = sigma_phi;
  filter.max_range = max_range;
}

void SimView::restart_from_config() {
  sanitize_config_values();
  reset_world_from_config();
  init_filter_at_true();
  reset_history();
  cache_dirty = true;
  save_config();
}

void SimView::reset_world_from_config() {
  robot_true = {};
  landmarks_true.clear();
  landmarks_true.reserve(static_cast<std::size_t>(landmark_count));

  std::mt19937 map_rng(static_cast<std::mt19937::result_type>(map_seed));
  std::uniform_real_distribution<double> x_dist(landmark_min_x,
                                                landmark_max_x);
  std::uniform_real_distribution<double> y_dist(landmark_min_y,
                                                landmark_max_y);

  for (int i = 0; i < landmark_count; ++i)
    landmarks_true.emplace_back(x_dist(map_rng), y_dist(map_rng));
  observation_buffer.reserve(landmarks_true.size());
}

void SimView::refresh_filter_cache() {
  if (!cache_dirty)
    return;

  double mx = 0.0;
  double my = 0.0;
  double mc = 0.0;
  double ms = 0.0;
  double w_sum = 0.0;
  double weight_sq_sum = 0.0;
  double best_weight = -1.0;
  int landmark_size = 0;
  cached_best_particle = -1;

  if (show_particles) {
    particle_plot_x.resize(filter.particles.size());
    particle_plot_y.resize(filter.particles.size());
  } else {
    particle_plot_x.clear();
    particle_plot_y.clear();
  }

  for (std::size_t i = 0; i < filter.particles.size(); ++i) {
    const Particle &p = filter.particles[i];
    mx += p.weight * p.x;
    my += p.weight * p.y;
    mc += p.weight * std::cos(p.theta);
    ms += p.weight * std::sin(p.theta);
    w_sum += p.weight;
    weight_sq_sum += p.weight * p.weight;
    if (p.weight > best_weight) {
      best_weight = p.weight;
      cached_best_particle = static_cast<int>(i);
    }
    landmark_size =
        std::max(landmark_size, static_cast<int>(p.landmarks.size()));

    if (show_particles) {
      particle_plot_x[i] = p.x;
      particle_plot_y[i] = p.y;
    }
  }

  if (w_sum > 0.0) {
    cached_mean_pose.x = mx / w_sum;
    cached_mean_pose.y = my / w_sum;
    cached_mean_pose.theta = std::atan2(ms, mc);
  } else {
    cached_mean_pose = {};
  }
  cached_effective_n = weight_sq_sum > 0.0 ? 1.0 / weight_sq_sum : 0.0;

  landmark_sum_buffer.resize(landmark_size);
  cached_landmark_seen_weights.resize(landmark_size);
  cached_mean_landmarks.resize(landmark_size);
  for (Eigen::Vector2d &sum : landmark_sum_buffer)
    sum.setZero();
  std::fill(cached_landmark_seen_weights.begin(),
            cached_landmark_seen_weights.end(), 0.0);

  for (const Particle &p : filter.particles) {
    for (int j = 0; j < static_cast<int>(p.landmarks.size()); ++j) {
      const LandmarkEKF &lm = p.landmarks[j];
      if (!lm.seen)
        continue;
      landmark_sum_buffer[j] += p.weight * lm.mu;
      cached_landmark_seen_weights[j] += p.weight;
    }
  }

  cached_majority_seen_landmark_count = 0;
  for (int j = 0; j < landmark_size; ++j) {
    const double seen_weight = cached_landmark_seen_weights[j];
    if (seen_weight > 0.0)
      cached_mean_landmarks[j] = landmark_sum_buffer[j] / seen_weight;
    else
      cached_mean_landmarks[j].setZero();
    if (seen_weight > 0.5)
      ++cached_majority_seen_landmark_count;
  }

  cached_active_landmark_count = 0;
  double landmark_sq_sum = 0.0;
  int landmark_rmse_count = 0;
  for (int j = 0; j < static_cast<int>(landmarks_true.size()); ++j) {
    if (!active_landmark(landmarks_true[j]))
      continue;
    ++cached_active_landmark_count;
    if (j >= landmark_size || cached_landmark_seen_weights[j] <= 0.0)
      continue;
    landmark_sq_sum +=
        (cached_mean_landmarks[j] - landmarks_true[j]).squaredNorm();
    ++landmark_rmse_count;
  }

  cached_pose_rmse =
      std::hypot(cached_mean_pose.x - robot_true.x,
                 cached_mean_pose.y - robot_true.y);
  cached_landmark_rmse =
      landmark_rmse_count > 0
          ? std::sqrt(landmark_sq_sum / static_cast<double>(landmark_rmse_count))
          : 0.0;
  cache_dirty = false;
}

void SimView::draw_robot_arrow(const Pose2D &p, ImU32 color, float scale) {
  const float xs[2] = {static_cast<float>(p.x),
                       static_cast<float>(p.x + scale * std::cos(p.theta))};
  const float ys[2] = {static_cast<float>(p.y),
                       static_cast<float>(p.y + scale * std::sin(p.theta))};
  ImPlot::PushStyleColor(ImPlotCol_Line, color);
  ImPlot::PlotLine("##arrow", xs, ys, 2);
  ImPlot::PopStyleColor();
}

void SimView::draw_sensor_fov(const Pose2D &p) {
  ImDrawList *draw = ImPlot::GetPlotDrawList();
  if (draw == nullptr || max_range <= 0.0)
    return;

  constexpr int segments = 72;
  fov_points.clear();

  if (fov_half >= kPi - 1e-4) {
    fov_points.reserve(segments);
    for (int i = 0; i < segments; ++i) {
      const double a = p.theta + 2.0 * kPi * i / segments;
      fov_points.push_back(
          ImPlot::PlotToPixels(p.x + max_range * std::cos(a),
                               p.y + max_range * std::sin(a)));
    }
  } else {
    fov_points.reserve(segments + 2);
    fov_points.push_back(ImPlot::PlotToPixels(p.x, p.y));
    for (int i = 0; i <= segments; ++i) {
      const double u = static_cast<double>(i) / segments;
      const double a = p.theta - fov_half + 2.0 * fov_half * u;
      fov_points.push_back(
          ImPlot::PlotToPixels(p.x + max_range * std::cos(a),
                               p.y + max_range * std::sin(a)));
    }
  }

  if (fov_points.size() < 3)
    return;

  draw->AddConvexPolyFilled(fov_points.data(),
                            static_cast<int>(fov_points.size()),
                            COLOR_FOV_FILL);
  draw->AddPolyline(fov_points.data(), static_cast<int>(fov_points.size()),
                    COLOR_FOV_LINE, ImDrawFlags_Closed, 1.5f);
}

void SimView::draw_covariance_ellipse(const Eigen::Vector2d &mu,
                                      const Eigen::Matrix2d &Sigma,
                                      ImU32 color) {
  if (!mu.allFinite() || !Sigma.allFinite())
    return;

  Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> solver(Sigma);
  if (solver.info() != Eigen::Success)
    return;

  const Eigen::Vector2d eigvals = solver.eigenvalues();
  const Eigen::Matrix2d eigvecs = solver.eigenvectors();

  const double l0 = std::max(eigvals(0), 1e-9);
  const double l1 = std::max(eigvals(1), 1e-9);

  constexpr double scale = 2.4477;
  const double a = scale * std::sqrt(l1);
  const double b = scale * std::sqrt(l0);
  const double angle = std::atan2(eigvecs(1, 1), eigvecs(0, 1));

  constexpr int N = 32;
  ellipse_x.resize(N + 1);
  ellipse_y.resize(N + 1);
  const double ca = std::cos(angle);
  const double sa = std::sin(angle);
  for (int i = 0; i <= N; ++i) {
    const double t = 2.0 * kPi * i / N;
    const double lx = a * std::cos(t);
    const double ly = b * std::sin(t);
    ellipse_x[i] = static_cast<float>(mu.x() + ca * lx - sa * ly);
    ellipse_y[i] = static_cast<float>(mu.y() + sa * lx + ca * ly);
  }

  ImPlot::PushStyleColor(ImPlotCol_Line, color);
  ImPlot::PlotLine("##ellipse", ellipse_x.data(), ellipse_y.data(), N + 1);
  ImPlot::PopStyleColor();
}

void SimView::init_filter_at_true() {
  filter = FastSLAM(sigma_v, sigma_w, sigma_r, sigma_phi, 42);
  filter.max_range = max_range;
  filter.init_gaussian(M, robot_true.x, robot_true.y, robot_true.theta,
                       kInitialStd);
  selected_particle = 0;
  last_resampled = false;
  cache_dirty = true;
}

void SimView::reset_history() {
  std::fill(hist_pose_rmse.begin(), hist_pose_rmse.end(), 0.0f);
  std::fill(hist_lm_rmse.begin(), hist_lm_rmse.end(), 0.0f);
  std::fill(hist_n_eff.begin(), hist_n_eff.end(), 0.0f);
  hist_idx = 0;
  hist_count = 0;
}

void SimView::update_history() {
  if (hist_pose_rmse.empty())
    return;

  hist_pose_rmse[hist_idx] = static_cast<float>(cached_pose_rmse);
  hist_lm_rmse[hist_idx] = static_cast<float>(cached_landmark_rmse);
  hist_n_eff[hist_idx] = static_cast<float>(cached_effective_n);
  hist_idx = (hist_idx + 1) % HIST_LEN;
  hist_count = std::min(hist_count + 1, HIST_LEN);
}

int SimView::active_landmark_count() const {
  return cached_active_landmark_count;
}

int SimView::majority_seen_landmark_count() const {
  return cached_majority_seen_landmark_count;
}

double SimView::landmark_seen_weight(int id) const {
  if (id < 0 || id >= static_cast<int>(cached_landmark_seen_weights.size()))
    return 0.0;
  return cached_landmark_seen_weights[id];
}

bool SimView::delete_landmark_near(double x, double y, double radius) {
  if (radius <= 0.0)
    return false;

  const Eigen::Vector2d target(x, y);
  double best_dist = std::numeric_limits<double>::infinity();
  int best_idx = -1;

  for (int i = 0; i < static_cast<int>(landmarks_true.size()); ++i) {
    if (!active_landmark(landmarks_true[i]))
      continue;
    const double dist = (landmarks_true[i] - target).norm();
    if (dist < best_dist) {
      best_dist = dist;
      best_idx = i;
    }
  }

  if (best_idx < 0 || best_dist > radius)
    return false;

  const double nan = std::numeric_limits<double>::quiet_NaN();
  landmarks_true[best_idx] = Eigen::Vector2d(nan, nan);
  cache_dirty = true;
  return true;
}
