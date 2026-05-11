#pragma once

#include "sim/sim2d.hpp"

#include <functional>
#include <string>
#include <vector>

inline constexpr char kDefaultBenchmarkConfigPath[] = "benchmark_config.ini";

struct BenchmarkConfig {
  std::vector<int> particle_counts;
  int steps = 1000;
  int metric_interval = 10;
  double dt = 0.05;
  double initial_std = 0.1;
  std::vector<unsigned> random_seeds = {42};
  std::string motion_pattern = "circle";
  double figure8_period = 12.0;
  int square_straight_steps = 80;
  int square_turn_steps = 20;
  bool write_timeseries = true;
  std::string csv_path = "benchmark_timeseries.csv";
};

struct BenchmarkResult {
  int particle_count = 0;
  int seed_runs = 1;
  int steps = 0;
  int resamples = 0;
  int samples = 0;
  int total_observations = 0;
  double runtime_ms = 0.0;
  double mean_pose_rmse = 0.0;
  double final_pose_rmse = 0.0;
  double max_pose_rmse = 0.0;
  double mean_landmark_rmse = 0.0;
  double final_landmark_rmse = 0.0;
  double mean_best_landmark_rmse = 0.0;
  double final_best_landmark_rmse = 0.0;
  double mean_effective_n = 0.0;
  double final_effective_n = 0.0;
  double mean_log_weight_span = 0.0;
  double final_log_weight_span = 0.0;
  double max_log_weight_span = 0.0;
  int final_mean_seen_landmarks = 0;
  int final_best_seen_landmarks = 0;
};

struct BenchmarkSample {
  int particle_count = 0;
  int step = 0;
  int observations = 0;
  bool resampled = false;
  double mean_observations = 0.0;
  double resample_rate = 0.0;
  double time = 0.0;
  double pose_rmse = 0.0;
  double mean_landmark_rmse = 0.0;
  double best_landmark_rmse = 0.0;
  double effective_n = 0.0;
  double log_weight_span = 0.0;
};

struct BenchmarkRun {
  BenchmarkResult result;
  std::vector<BenchmarkSample> samples;
};

struct BenchmarkProgress {
  int total_runs = 0;
  int run_index = 0;
  int completed_runs = 0;
  int seed_run = 0;
  int seed_runs = 1;
  int particle_count = 0;
  int step = 0;
  int total_steps = 0;
  int completed_steps = 0;
  int total_steps_all = 0;
  bool complete = false;
};

using BenchmarkProgressCallback =
    std::function<void(const BenchmarkProgress &progress)>;

void sanitize_benchmark_config(BenchmarkConfig &config);
bool load_benchmark_config(BenchmarkConfig &config, const char *path);
bool save_benchmark_config(const BenchmarkConfig &config, const char *path);
std::vector<BenchmarkRun>
run_benchmark_suite_detailed(const SimConfig &sim_config,
                             const BenchmarkConfig &bench,
                             const BenchmarkProgressCallback &progress = {});
std::vector<BenchmarkResult> run_benchmark_suite(const SimConfig &sim_config,
                                                 const BenchmarkConfig &bench);
void print_benchmark_summary(const std::vector<BenchmarkResult> &results);
