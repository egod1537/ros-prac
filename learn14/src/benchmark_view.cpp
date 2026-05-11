#include "benchmark.hpp"
#include "sim/sim_config.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <future>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace {
struct SharedProgress {
  std::mutex mutex;
  BenchmarkProgress value;
};

struct PlotRun {
  int particle_count = 0;
  std::string label;
  std::vector<double> time;
  std::vector<double> pose_rmse;
  std::vector<double> mean_landmark_rmse;
  std::vector<double> best_landmark_rmse;
  std::vector<double> effective_n;
  std::vector<double> log_weight_span;
};

struct AppState {
  SimConfig sim_config;
  BenchmarkConfig benchmark_config;
  std::array<char, 256> particle_counts_text{};
  std::array<char, 256> random_seeds_text{};
  std::array<char, 256> csv_path_text{};
  std::vector<BenchmarkRun> runs;
  std::vector<PlotRun> plot_runs;
  std::future<std::vector<BenchmarkRun>> future;
  std::shared_ptr<SharedProgress> progress = std::make_shared<SharedProgress>();
  bool running = false;
  int selected_metric = 0;
  int selected_motion = 0;
  std::string status = "Ready";
};

constexpr const char *kMotionPatterns[] = {"circle", "straight", "spin",
                                           "figure8", "square"};
constexpr const char *kMetricLabels[] = {"Pose RMSE", "Mean Landmark RMSE",
                                         "Best Landmark RMSE",
                                         "Effective N (pre-resample)",
                                         "Log Weight Span"};

struct SeedEdit {
  bool changed = false;
  bool committed = false;
};

bool slider_double(const char *label, double *value, double min_value,
                   double max_value, const char *format = "%.3f") {
  return ImGui::SliderScalar(label, ImGuiDataType_Double, value, &min_value,
                             &max_value, format);
}

std::mt19937 &seed_rng() {
  static std::mt19937 rng(std::random_device{}());
  return rng;
}

int random_map_seed() {
  std::uniform_int_distribution<int> dist(sim_config::kMapSeedMin,
                                          sim_config::kMapSeedMax);
  return dist(seed_rng());
}

SeedEdit input_map_seed(const char *label, int *value, const char *button_id) {
  SeedEdit edit;
  edit.changed =
      ImGui::InputScalar(label, ImGuiDataType_S32, value, nullptr, nullptr,
                         "%d");
  edit.committed = ImGui::IsItemDeactivatedAfterEdit();
  ImGui::SameLine();
  if (ImGui::Button(button_id)) {
    *value = random_map_seed();
    edit.changed = true;
    edit.committed = true;
  }
  return edit;
}

std::string particle_counts_to_string(const std::vector<int> &counts) {
  std::ostringstream out;
  for (std::size_t i = 0; i < counts.size(); ++i) {
    if (i > 0)
      out << ',';
    out << counts[i];
  }
  return out.str();
}

std::string random_seeds_to_string(const std::vector<unsigned> &seeds) {
  std::ostringstream out;
  for (std::size_t i = 0; i < seeds.size(); ++i) {
    if (i > 0)
      out << ',';
    out << seeds[i];
  }
  return out.str();
}

std::vector<int> parse_particle_counts(const char *text) {
  std::vector<int> counts;
  std::stringstream ss(text);
  std::string item;
  while (std::getline(ss, item, ',')) {
    try {
      const int value = std::stoi(item);
      if (value > 0)
        counts.push_back(value);
    } catch (...) {
    }
  }
  return counts;
}

std::vector<unsigned> parse_random_seeds(const char *text) {
  std::vector<unsigned> seeds;
  std::stringstream ss(text);
  std::string item;
  while (std::getline(ss, item, ',')) {
    try {
      seeds.push_back(static_cast<unsigned>(std::stoul(item)));
    } catch (...) {
    }
  }
  return seeds;
}

void sync_particle_counts_text(AppState &state) {
  const std::string text =
      particle_counts_to_string(state.benchmark_config.particle_counts);
  std::snprintf(state.particle_counts_text.data(),
                state.particle_counts_text.size(), "%s", text.c_str());
}

void sync_random_seeds_text(AppState &state) {
  const std::string text =
      random_seeds_to_string(state.benchmark_config.random_seeds);
  std::snprintf(state.random_seeds_text.data(),
                state.random_seeds_text.size(), "%s", text.c_str());
}

void sync_csv_path_text(AppState &state) {
  std::snprintf(state.csv_path_text.data(), state.csv_path_text.size(), "%s",
                state.benchmark_config.csv_path.c_str());
}

void sync_motion_index(AppState &state) {
  state.selected_motion = 0;
  for (int i = 0; i < static_cast<int>(std::size(kMotionPatterns)); ++i) {
    if (state.benchmark_config.motion_pattern == kMotionPatterns[i]) {
      state.selected_motion = i;
      return;
    }
  }
}

void load_configs(AppState &state) {
  sim_config::load(state.sim_config);
  if (!load_benchmark_config(state.benchmark_config,
                             kDefaultBenchmarkConfigPath)) {
    state.status = "benchmark_config.ini not found; using defaults";
  } else {
    state.status = "Configs loaded";
  }
  if (state.benchmark_config.particle_counts.empty())
    state.benchmark_config.particle_counts.push_back(
        state.sim_config.particle_count);
  sync_particle_counts_text(state);
  sync_random_seeds_text(state);
  sync_csv_path_text(state);
  sync_motion_index(state);
}

void build_plot_runs(AppState &state) {
  state.plot_runs.clear();
  state.plot_runs.reserve(state.runs.size());
  for (const BenchmarkRun &run : state.runs) {
    PlotRun plot;
    plot.particle_count = run.result.particle_count;
    plot.label = std::to_string(plot.particle_count);
    plot.time.reserve(run.samples.size());
    plot.pose_rmse.reserve(run.samples.size());
    plot.mean_landmark_rmse.reserve(run.samples.size());
    plot.best_landmark_rmse.reserve(run.samples.size());
    plot.effective_n.reserve(run.samples.size());
    plot.log_weight_span.reserve(run.samples.size());

    for (const BenchmarkSample &sample : run.samples) {
      plot.time.push_back(sample.time);
      plot.pose_rmse.push_back(sample.pose_rmse);
      plot.mean_landmark_rmse.push_back(sample.mean_landmark_rmse);
      plot.best_landmark_rmse.push_back(sample.best_landmark_rmse);
      plot.effective_n.push_back(sample.effective_n);
      plot.log_weight_span.push_back(sample.log_weight_span);
    }
    state.plot_runs.push_back(std::move(plot));
  }
}

const std::vector<double> &metric_values(const PlotRun &run, int metric) {
  switch (metric) {
  case 0:
    return run.pose_rmse;
  case 1:
    return run.mean_landmark_rmse;
  case 2:
    return run.best_landmark_rmse;
  case 3:
    return run.effective_n;
  default:
    return run.log_weight_span;
  }
}

BenchmarkProgress progress_snapshot(const AppState &state) {
  std::lock_guard<std::mutex> lock(state.progress->mutex);
  return state.progress->value;
}

void set_progress(const std::shared_ptr<SharedProgress> &shared,
                  const BenchmarkProgress &progress) {
  std::lock_guard<std::mutex> lock(shared->mutex);
  shared->value = progress;
}

void poll_benchmark(AppState &state) {
  if (!state.running || !state.future.valid())
    return;

  using namespace std::chrono_literals;
  if (state.future.wait_for(0ms) != std::future_status::ready)
    return;

  state.runs = state.future.get();
  build_plot_runs(state);
  state.running = false;
  state.status = state.runs.empty() ? "Benchmark produced no runs"
                                    : "Benchmark complete";
}

void start_benchmark(AppState &state) {
  state.benchmark_config.particle_counts =
      parse_particle_counts(state.particle_counts_text.data());
  if (state.benchmark_config.particle_counts.empty())
    state.benchmark_config.particle_counts.push_back(
        state.sim_config.particle_count);
  state.benchmark_config.random_seeds =
      parse_random_seeds(state.random_seeds_text.data());
  state.benchmark_config.motion_pattern = kMotionPatterns[state.selected_motion];
  state.benchmark_config.csv_path = state.csv_path_text.data();
  sanitize_benchmark_config(state.benchmark_config);
  sim_config::sanitize(state.sim_config);
  save_benchmark_config(state.benchmark_config, kDefaultBenchmarkConfigPath);
  sim_config::save(state.sim_config);

  const SimConfig sim = state.sim_config;
  const BenchmarkConfig bench = state.benchmark_config;
  set_progress(state.progress, BenchmarkProgress{});
  state.status = "Benchmark running";
  state.running = true;
  const std::shared_ptr<SharedProgress> progress = state.progress;
  state.future = std::async(std::launch::async, [sim, bench, progress]() {
    return run_benchmark_suite_detailed(
        sim, bench, [progress](const BenchmarkProgress &value) {
          set_progress(progress, value);
        });
  });
}

void persist_sim_config(AppState &state) {
  sim_config::sanitize(state.sim_config);
  sim_config::save(state.sim_config);
  state.status = "sim_config.ini saved";
}

void persist_benchmark_config(AppState &state, bool sync_text = false) {
  state.benchmark_config.particle_counts =
      parse_particle_counts(state.particle_counts_text.data());
  state.benchmark_config.random_seeds =
      parse_random_seeds(state.random_seeds_text.data());
  state.benchmark_config.motion_pattern = kMotionPatterns[state.selected_motion];
  state.benchmark_config.csv_path = state.csv_path_text.data();
  sanitize_benchmark_config(state.benchmark_config);
  if (state.benchmark_config.particle_counts.empty())
    state.benchmark_config.particle_counts.push_back(
        state.sim_config.particle_count);
  save_benchmark_config(state.benchmark_config, kDefaultBenchmarkConfigPath);
  if (sync_text) {
    sync_particle_counts_text(state);
    sync_random_seeds_text(state);
    sync_csv_path_text(state);
  }
  state.status = "benchmark_config.ini saved";
}

void render_sim_config_editor(AppState &state) {
  if (!ImGui::CollapsingHeader("Simulation Config",
                               ImGuiTreeNodeFlags_DefaultOpen))
    return;

  bool config_changed = false;
  bool save_requested = false;
  ImGui::SeparatorText("Config");

  ImGui::SeparatorText("Control");
  if (slider_double("linear speed", &state.sim_config.linear_speed,
                    sim_config::kLinearSpeedMin,
                    sim_config::kLinearSpeedMax, "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("angular speed", &state.sim_config.angular_speed,
                    sim_config::kAngularSpeedMin,
                    sim_config::kAngularSpeedMax, "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Noise");
  if (slider_double("sigma_v", &state.sim_config.sigma_v,
                    sim_config::kSigmaMin, sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_w", &state.sim_config.sigma_w,
                    sim_config::kSigmaMin, sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_r", &state.sim_config.sigma_r,
                    sim_config::kSigmaMin, sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("sigma_phi", &state.sim_config.sigma_phi,
                    sim_config::kSigmaMin, sim_config::kSigmaMax, "%.4f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Sensor");
  if (slider_double("max_range", &state.sim_config.max_range,
                    sim_config::kMaxRangeMin, sim_config::kMaxRangeMax,
                    "%.2f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("fov_half", &state.sim_config.fov_half,
                    sim_config::kFovHalfMin, sim_config::kFovHalfMax,
                    "%.3f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  ImGui::SeparatorText("Landmarks");
  if (ImGui::SliderInt("landmarks", &state.sim_config.landmark_count,
                       sim_config::kLandmarkCountMin,
                       sim_config::kLandmarkCountMax)) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  const SeedEdit map_seed_edit =
      input_map_seed("map seed", &state.sim_config.map_seed,
                     "Random##benchmark_sim_map_seed");
  if (map_seed_edit.changed)
    config_changed = true;
  save_requested |= map_seed_edit.committed;
  if (slider_double("lm min x", &state.sim_config.landmark_min_x,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("lm max x", &state.sim_config.landmark_max_x,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("lm min y", &state.sim_config.landmark_min_y,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();
  if (slider_double("lm max y", &state.sim_config.landmark_max_y,
                    sim_config::kLandmarkRangeMin,
                    sim_config::kLandmarkRangeMax, "%.1f")) {
    config_changed = true;
  }
  save_requested |= ImGui::IsItemDeactivatedAfterEdit();

  if (config_changed)
    sim_config::sanitize(state.sim_config);
  if (save_requested)
    persist_sim_config(state);
}

void render_benchmark_config_editor(AppState &state) {
  bool changed = false;

  if (!ImGui::CollapsingHeader("Benchmark Config",
                               ImGuiTreeNodeFlags_DefaultOpen))
    return;

  ImGui::InputText("particle counts", state.particle_counts_text.data(),
                   state.particle_counts_text.size());
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    state.benchmark_config.particle_counts =
        parse_particle_counts(state.particle_counts_text.data());
    persist_benchmark_config(state, true);
  }
  ImGui::InputText("random seeds", state.random_seeds_text.data(),
                   state.random_seeds_text.size());
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    state.benchmark_config.random_seeds =
        parse_random_seeds(state.random_seeds_text.data());
    persist_benchmark_config(state, true);
  }

  changed |= ImGui::InputInt("steps", &state.benchmark_config.steps);
  changed |=
      ImGui::InputInt("metric interval", &state.benchmark_config.metric_interval);
  changed |= ImGui::InputDouble("dt", &state.benchmark_config.dt, 0.01, 0.1,
                                "%.3f");
  changed |= ImGui::InputDouble("initial std",
                                &state.benchmark_config.initial_std, 0.01, 0.1,
                                "%.3f");

  if (ImGui::Combo("motion", &state.selected_motion, kMotionPatterns,
                   static_cast<int>(std::size(kMotionPatterns)))) {
    state.benchmark_config.motion_pattern = kMotionPatterns[state.selected_motion];
    changed = true;
  }
  if (state.selected_motion == 3) {
    changed |= ImGui::InputDouble("figure8 period",
                                  &state.benchmark_config.figure8_period, 0.5,
                                  1.0, "%.2f");
  }
  if (state.selected_motion == 4) {
    changed |= ImGui::InputInt("square straight steps",
                               &state.benchmark_config.square_straight_steps);
    changed |= ImGui::InputInt("square turn steps",
                               &state.benchmark_config.square_turn_steps);
  }
  changed |= ImGui::Checkbox("write timeseries csv",
                             &state.benchmark_config.write_timeseries);
  ImGui::InputText("csv path", state.csv_path_text.data(),
                   state.csv_path_text.size());
  if (ImGui::IsItemDeactivatedAfterEdit()) {
    state.benchmark_config.csv_path = state.csv_path_text.data();
    persist_benchmark_config(state, true);
  }

  if (changed)
    persist_benchmark_config(state, true);
}

void render_progress(const AppState &state) {
  const BenchmarkProgress progress = progress_snapshot(state);
  if (!state.running && progress.total_steps_all <= 0)
    return;

  const float fraction =
      progress.total_steps_all > 0
          ? static_cast<float>(progress.completed_steps) /
                static_cast<float>(progress.total_steps_all)
          : 0.0f;
  char label[64];
  std::snprintf(label, sizeof(label), "%.1f%%", fraction * 100.0f);

  ImGui::SeparatorText("Progress");
  ImGui::ProgressBar(std::clamp(fraction, 0.0f, 1.0f), ImVec2(-1, 0), label);
  if (state.running) {
    ImGui::Text("run %d/%d  particles %d", progress.run_index,
                progress.total_runs, progress.particle_count);
    ImGui::Text("seed %d/%d", progress.seed_run, progress.seed_runs);
    ImGui::Text("step %d/%d  total %d/%d", progress.step,
                progress.total_steps, progress.completed_steps,
                progress.total_steps_all);
  } else if (progress.complete) {
    ImGui::TextUnformatted("complete");
  }
}

void render_config_panel(AppState &state) {
  ImGui::SeparatorText("Scenario");
  ImGui::Text("sim_config.ini");
  ImGui::Text("landmarks: %d  map_seed: %d", state.sim_config.landmark_count,
              state.sim_config.map_seed);
  ImGui::Text("speed: %.2f m/s  %.2f rad/s", state.sim_config.linear_speed,
              state.sim_config.angular_speed);
  ImGui::Text("noise: v %.4f  w %.4f  r %.4f  phi %.4f",
              state.sim_config.sigma_v, state.sim_config.sigma_w,
              state.sim_config.sigma_r, state.sim_config.sigma_phi);

  if (ImGui::Button("Reload Configs") && !state.running)
    load_configs(state);

  if (state.running)
    ImGui::BeginDisabled();

  render_benchmark_config_editor(state);
  render_sim_config_editor(state);

  if (ImGui::Button("Run Benchmark"))
    start_benchmark(state);

  if (state.running)
    ImGui::EndDisabled();

  render_progress(state);
  ImGui::Text("Status: %s", state.status.c_str());
}

void render_summary_table(const AppState &state) {
  ImGui::SeparatorText("Summary");
  if (state.runs.empty()) {
    ImGui::TextUnformatted("No benchmark results yet.");
    return;
  }

  constexpr ImGuiTableFlags flags =
      ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
      ImGuiTableFlags_ScrollX | ImGuiTableFlags_Resizable;
  if (!ImGui::BeginTable("summary_table", 15, flags, ImVec2(-1, 220)))
    return;

  ImGui::TableSetupColumn("particles");
  ImGui::TableSetupColumn("seeds");
  ImGui::TableSetupColumn("runtime ms");
  ImGui::TableSetupColumn("avg resamples");
  ImGui::TableSetupColumn("pose mean");
  ImGui::TableSetupColumn("pose final");
  ImGui::TableSetupColumn("mean LM avg");
  ImGui::TableSetupColumn("mean LM final");
  ImGui::TableSetupColumn("best LM avg");
  ImGui::TableSetupColumn("best LM final");
  ImGui::TableSetupColumn("N_eff avg pre");
  ImGui::TableSetupColumn("N_eff final pre");
  ImGui::TableSetupColumn("logw final");
  ImGui::TableSetupColumn("logw max");
  ImGui::TableSetupColumn("seen");
  ImGui::TableHeadersRow();

  for (const BenchmarkRun &run : state.runs) {
    const BenchmarkResult &r = run.result;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%d", r.particle_count);
    ImGui::TableNextColumn();
    ImGui::Text("%d", r.seed_runs);
    ImGui::TableNextColumn();
    ImGui::Text("%.1f", r.runtime_ms);
    ImGui::TableNextColumn();
    ImGui::Text("%d", r.resamples);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.mean_pose_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.final_pose_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.mean_landmark_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.final_landmark_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.mean_best_landmark_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.4f", r.final_best_landmark_rmse);
    ImGui::TableNextColumn();
    ImGui::Text("%.1f", r.mean_effective_n);
    ImGui::TableNextColumn();
    ImGui::Text("%.1f", r.final_effective_n);
    ImGui::TableNextColumn();
    ImGui::Text("%.2f", r.final_log_weight_span);
    ImGui::TableNextColumn();
    ImGui::Text("%.2f", r.max_log_weight_span);
    ImGui::TableNextColumn();
    ImGui::Text("%d/%d", r.final_mean_seen_landmarks,
                r.final_best_seen_landmarks);
  }
  ImGui::EndTable();
}

void render_metric_plot(AppState &state) {
  ImGui::SeparatorText("Metrics");
  ImGui::Combo("metric", &state.selected_metric, kMetricLabels,
               static_cast<int>(std::size(kMetricLabels)));

  if (state.plot_runs.empty())
    return;

  if (!ImPlot::BeginPlot("Benchmark Metrics", ImVec2(-1, -1)))
    return;

  ImPlot::SetupAxes("time [s]", kMetricLabels[state.selected_metric]);
  for (const PlotRun &run : state.plot_runs) {
    const std::vector<double> &ys = metric_values(run, state.selected_metric);
    if (run.time.empty() || ys.empty())
      continue;
    ImPlot::PlotLine(run.label.c_str(), run.time.data(), ys.data(),
                     static_cast<int>(std::min(run.time.size(), ys.size())));
  }
  ImPlot::EndPlot();
}

bool init_glfw_window(GLFWwindow **window) {
  if (!glfwInit()) {
    std::fprintf(stderr, "glfwInit failed\n");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  *window = glfwCreateWindow(1500, 900, "learn14 Benchmark", nullptr, nullptr);
  if (*window == nullptr) {
    std::fprintf(stderr, "glfwCreateWindow failed\n");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(*window);
  glfwSwapInterval(1);
  return true;
}

int run_headless(int argc, char **argv) {
  int arg = 2;
  const char *sim_config_path =
      arg < argc ? argv[arg++] : sim_config::kDefaultConfigPath;
  const char *benchmark_config_path =
      arg < argc ? argv[arg++] : kDefaultBenchmarkConfigPath;

  SimConfig sim_config;
  sim_config::load(sim_config, sim_config_path);

  BenchmarkConfig benchmark_config;
  if (!load_benchmark_config(benchmark_config, benchmark_config_path)) {
    std::fprintf(stderr,
                 "benchmark config not found: %s; using built-in defaults\n",
                 benchmark_config_path);
  }

  const std::vector<BenchmarkResult> results =
      run_benchmark_suite(sim_config, benchmark_config);
  print_benchmark_summary(results);

  if (benchmark_config.write_timeseries && !benchmark_config.csv_path.empty())
    std::cout << "timeseries_csv=" << benchmark_config.csv_path << '\n';

  return results.empty() ? 1 : 0;
}

void print_usage(const char *program) {
  std::cout << "usage:\n"
            << "  " << program << "\n"
            << "  " << program
            << " --headless [sim_config.ini] [benchmark_config.ini]\n";
}
} // namespace

int main(int argc, char **argv) {
  if (argc > 1) {
    if (std::strcmp(argv[1], "--headless") == 0 ||
        std::strcmp(argv[1], "--cli") == 0) {
      return run_headless(argc, argv);
    }
    if (std::strcmp(argv[1], "--help") == 0 ||
        std::strcmp(argv[1], "-h") == 0) {
      print_usage(argv[0]);
      return 0;
    }
  }

  GLFWwindow *window = nullptr;
  if (!init_glfw_window(&window))
    return 1;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::StyleColorsDark();
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true) ||
      !ImGui_ImplOpenGL3_Init("#version 330")) {
    std::fprintf(stderr, "ImGui backend init failed\n");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  AppState state;
  load_configs(state);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    poll_benchmark(state);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(viewport->WorkSize, ImGuiCond_Always);
    ImGui::Begin("learn14 Benchmark Viewer", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoResize);

    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float left_w = std::max(360.0f, avail.x * 0.28f);

    ImGui::BeginChild("config_panel", ImVec2(left_w, 0),
                      ImGuiChildFlags_Borders);
    render_config_panel(state);
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("results_panel", ImVec2(0, 0), ImGuiChildFlags_Borders);
    render_summary_table(state);
    render_metric_plot(state);
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

  persist_benchmark_config(state);
  persist_sim_config(state);

  if (state.running && state.future.valid())
    state.future.wait();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
