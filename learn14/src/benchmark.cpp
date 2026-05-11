#include "benchmark.hpp"

#include "fastslam.hpp"
#include "geom.hpp"
#include "sim/sim_config.hpp"

#include <Eigen/Dense>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace {
constexpr double kPi = 3.14159265358979323846;

struct MotionCommand {
  double dist = 0.0;
  double dtheta = 0.0;
};

struct LandmarkMetric {
  double rmse = 0.0;
  int seen = 0;
};

std::string trim(const std::string &s) {
  const std::size_t first = s.find_first_not_of(" \t\r\n");
  if (first == std::string::npos)
    return {};
  const std::size_t last = s.find_last_not_of(" \t\r\n");
  return s.substr(first, last - first + 1);
}

bool parse_bool(const std::string &value) {
  return value == "1" || value == "true" || value == "TRUE" ||
         value == "yes" || value == "YES" || value == "on" ||
         value == "ON";
}

std::vector<int> parse_int_list(const std::string &value) {
  std::vector<int> result;
  std::stringstream ss(value);
  std::string item;
  while (std::getline(ss, item, ',')) {
    try {
      result.push_back(std::stoi(trim(item)));
    } catch (...) {
    }
  }
  return result;
}

std::vector<unsigned> parse_uint_list(const std::string &value) {
  std::vector<unsigned> result;
  std::stringstream ss(value);
  std::string item;
  while (std::getline(ss, item, ',')) {
    try {
      result.push_back(static_cast<unsigned>(std::stoul(trim(item))));
    } catch (...) {
    }
  }
  return result;
}

unsigned mix_seed(unsigned seed, unsigned salt) {
  unsigned x = seed + salt + 0x9e3779b9U;
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}

int map_seed_from_trial_seed(unsigned seed) {
  const unsigned range =
      static_cast<unsigned>(sim_config::kMapSeedMax -
                            sim_config::kMapSeedMin + 1);
  return sim_config::kMapSeedMin +
         static_cast<int>(mix_seed(seed, 0x13579bdfU) % range);
}

std::vector<Eigen::Vector2d> generate_landmarks(const SimConfig &config) {
  std::mt19937 rng(static_cast<std::mt19937::result_type>(config.map_seed));
  std::uniform_real_distribution<double> x_dist(config.landmark_min_x,
                                                config.landmark_max_x);
  std::uniform_real_distribution<double> y_dist(config.landmark_min_y,
                                                config.landmark_max_y);

  std::vector<Eigen::Vector2d> landmarks;
  landmarks.reserve(static_cast<std::size_t>(config.landmark_count));
  for (int i = 0; i < config.landmark_count; ++i)
    landmarks.emplace_back(x_dist(rng), y_dist(rng));
  return landmarks;
}

void step_pose(Pose2D &pose, double dist, double dtheta) {
  const double mid = pose.theta + 0.5 * dtheta;
  pose.x += dist * std::cos(mid);
  pose.y += dist * std::sin(mid);
  pose.theta = wrap(pose.theta + dtheta);
}

MotionCommand make_motion_command(const SimConfig &sim,
                                  const BenchmarkConfig &bench, int step) {
  const double t = static_cast<double>(step) * bench.dt;
  const double dist = sim.linear_speed * bench.dt;
  const double turn = sim.angular_speed * bench.dt;

  if (bench.motion_pattern == "straight")
    return {dist, 0.0};
  if (bench.motion_pattern == "spin")
    return {0.0, turn};
  if (bench.motion_pattern == "figure8") {
    const double period = std::max(bench.figure8_period, bench.dt);
    return {dist, turn * std::sin(2.0 * kPi * t / period)};
  }
  if (bench.motion_pattern == "square") {
    const int straight_steps = std::max(1, bench.square_straight_steps);
    const int turn_steps = std::max(1, bench.square_turn_steps);
    const int phase = step % (straight_steps + turn_steps);
    if (phase < straight_steps)
      return {dist, 0.0};
    return {0.0, (0.5 * kPi) / static_cast<double>(turn_steps)};
  }

  return {dist, turn};
}

void simulate_observations(const Pose2D &pose,
                           const std::vector<Eigen::Vector2d> &landmarks,
                           const SimConfig &config, std::mt19937 &rng,
                           std::vector<Observation> &obs) {
  obs.clear();
  std::normal_distribution<double> r_noise(0.0, config.sigma_r);
  std::normal_distribution<double> phi_noise(0.0, config.sigma_phi);
  const double max_range_sq = config.max_range * config.max_range;

  for (int i = 0; i < static_cast<int>(landmarks.size()); ++i) {
    const Eigen::Vector2d &lm = landmarks[i];
    const double dx = lm.x() - pose.x;
    const double dy = lm.y() - pose.y;
    const double q = dx * dx + dy * dy;
    if (q > max_range_sq)
      continue;

    const double range = std::sqrt(q);
    const double bearing = wrap(std::atan2(dy, dx) - pose.theta);
    if (std::abs(bearing) > config.fov_half)
      continue;

    Observation z;
    z.id = i;
    z.r = std::max(1e-6, range + r_noise(rng));
    z.phi = wrap(bearing + phi_noise(rng));
    obs.push_back(z);
  }
}

Pose2D weighted_mean_pose(const FastSLAM &filter) {
  double mx = 0.0;
  double my = 0.0;
  double mc = 0.0;
  double ms = 0.0;
  double w_sum = 0.0;

  for (const Particle &p : filter.particles) {
    mx += p.weight * p.x;
    my += p.weight * p.y;
    mc += p.weight * std::cos(p.theta);
    ms += p.weight * std::sin(p.theta);
    w_sum += p.weight;
  }

  Pose2D mean;
  if (w_sum > 0.0) {
    mean.x = mx / w_sum;
    mean.y = my / w_sum;
    mean.theta = std::atan2(ms, mc);
  }
  return mean;
}

double pose_rmse(const Pose2D &truth, const Pose2D &estimate) {
  return std::hypot(estimate.x - truth.x, estimate.y - truth.y);
}

LandmarkMetric mean_landmark_rmse(
    const FastSLAM &filter, const std::vector<Eigen::Vector2d> &truth) {
  std::vector<Eigen::Vector2d> sums(truth.size(), Eigen::Vector2d::Zero());
  std::vector<double> weights(truth.size(), 0.0);

  for (const Particle &p : filter.particles) {
    const int limit =
        std::min(static_cast<int>(truth.size()), static_cast<int>(p.landmarks.size()));
    for (int i = 0; i < limit; ++i) {
      const LandmarkEKF &lm = p.landmarks[i];
      if (!lm.seen)
        continue;
      sums[i] += p.weight * lm.mu;
      weights[i] += p.weight;
    }
  }

  double sq_sum = 0.0;
  int seen = 0;
  for (int i = 0; i < static_cast<int>(truth.size()); ++i) {
    if (weights[i] <= 0.0)
      continue;
    const Eigen::Vector2d mean = sums[i] / weights[i];
    sq_sum += (mean - truth[i]).squaredNorm();
    ++seen;
  }

  LandmarkMetric metric;
  metric.seen = seen;
  metric.rmse = seen > 0 ? std::sqrt(sq_sum / static_cast<double>(seen)) : 0.0;
  return metric;
}

int best_particle_index(const FastSLAM &filter) {
  int best = -1;
  double best_weight = -std::numeric_limits<double>::infinity();
  for (int i = 0; i < static_cast<int>(filter.particles.size()); ++i) {
    if (filter.particles[i].weight > best_weight) {
      best_weight = filter.particles[i].weight;
      best = i;
    }
  }
  return best;
}

LandmarkMetric best_landmark_rmse(
    const FastSLAM &filter, const std::vector<Eigen::Vector2d> &truth) {
  LandmarkMetric metric;
  const int best = best_particle_index(filter);
  if (best < 0)
    return metric;

  const Particle &p = filter.particles[best];
  const int limit =
      std::min(static_cast<int>(truth.size()), static_cast<int>(p.landmarks.size()));
  double sq_sum = 0.0;
  for (int i = 0; i < limit; ++i) {
    const LandmarkEKF &lm = p.landmarks[i];
    if (!lm.seen)
      continue;
    sq_sum += (lm.mu - truth[i]).squaredNorm();
    ++metric.seen;
  }

  metric.rmse =
      metric.seen > 0 ? std::sqrt(sq_sum / static_cast<double>(metric.seen))
                      : 0.0;
  return metric;
}

double effective_n(const FastSLAM &filter) {
  double sq_sum = 0.0;
  for (const Particle &p : filter.particles)
    sq_sum += p.weight * p.weight;
  return sq_sum > 0.0 ? 1.0 / sq_sum : 0.0;
}

void write_timeseries_header(std::ofstream &out) {
  out << "particle_count,seed_runs,step,time,pose_rmse,mean_landmark_rmse,"
         "best_landmark_rmse,effective_n_pre_resample,log_weight_span,"
         "mean_observations,resample_rate\n";
}

BenchmarkRun run_once(const SimConfig &sim, const BenchmarkConfig &bench,
                      int particle_count, int run_index, int total_runs,
                      int seed_run, int seed_runs,
                      unsigned filter_seed, unsigned observation_seed,
                      int completed_steps_before, int total_steps_all,
                      const BenchmarkProgressCallback &progress_cb) {
  const std::vector<Eigen::Vector2d> landmarks = generate_landmarks(sim);
  std::mt19937 obs_rng(
      static_cast<std::mt19937::result_type>(observation_seed));

  Pose2D truth;
  FastSLAM filter(sim.sigma_v, sim.sigma_w, sim.sigma_r, sim.sigma_phi,
                  filter_seed);
  filter.max_range = sim.max_range;
  filter.init_gaussian(particle_count, truth.x, truth.y, truth.theta,
                       bench.initial_std);

  std::vector<Observation> observations;
  observations.reserve(landmarks.size());

  BenchmarkRun run;
  BenchmarkResult &result = run.result;
  result.particle_count = particle_count;
  result.seed_runs = 1;
  result.steps = bench.steps;
  run.samples.reserve(static_cast<std::size_t>(
      bench.steps / std::max(1, bench.metric_interval) + 1));

  const auto report_progress = [&](int step, bool run_complete) {
    if (!progress_cb)
      return;

    BenchmarkProgress progress;
    progress.total_runs = total_runs;
    progress.run_index = run_index;
    progress.completed_runs = run_complete ? run_index : run_index - 1;
    progress.seed_run = seed_run;
    progress.seed_runs = seed_runs;
    progress.particle_count = particle_count;
    progress.step = std::clamp(step, 0, bench.steps);
    progress.total_steps = bench.steps;
    progress.completed_steps =
        std::min(total_steps_all, completed_steps_before + progress.step);
    progress.total_steps_all = total_steps_all;
    progress.complete = false;
    progress_cb(progress);
  };

  const int progress_interval = std::max(1, bench.steps / 200);
  report_progress(0, false);

  const auto start = std::chrono::steady_clock::now();
  for (int step = 0; step < bench.steps; ++step) {
    const MotionCommand cmd = make_motion_command(sim, bench, step);
    step_pose(truth, cmd.dist, cmd.dtheta);
    filter.predict(cmd.dist, cmd.dtheta);
    simulate_observations(truth, landmarks, sim, obs_rng, observations);
    filter.observe(observations);

    if (filter.last_resampled)
      ++result.resamples;
    result.total_observations += static_cast<int>(observations.size());

    const int steps_done = step + 1;
    if (steps_done == bench.steps || steps_done % progress_interval == 0)
      report_progress(steps_done, false);

    const bool sample_step =
        step == bench.steps - 1 ||
        (bench.metric_interval > 0 && step % bench.metric_interval == 0);
    if (!sample_step)
      continue;

    const Pose2D mean_pose = weighted_mean_pose(filter);
    const double pose_error = pose_rmse(truth, mean_pose);
    const LandmarkMetric mean_lm = mean_landmark_rmse(filter, landmarks);
    const LandmarkMetric best_lm = best_landmark_rmse(filter, landmarks);
    const double neff = filter.last_effective_n;
    const double log_weight_span = filter.last_log_weight_span;

    ++result.samples;
    result.mean_pose_rmse += pose_error;
    result.max_pose_rmse = std::max(result.max_pose_rmse, pose_error);
    result.mean_landmark_rmse += mean_lm.rmse;
    result.mean_best_landmark_rmse += best_lm.rmse;
    result.mean_effective_n += neff;
    result.mean_log_weight_span += log_weight_span;
    result.max_log_weight_span =
        std::max(result.max_log_weight_span, log_weight_span);
    result.final_pose_rmse = pose_error;
    result.final_landmark_rmse = mean_lm.rmse;
    result.final_best_landmark_rmse = best_lm.rmse;
    result.final_effective_n = neff;
    result.final_log_weight_span = log_weight_span;
    result.final_mean_seen_landmarks = mean_lm.seen;
    result.final_best_seen_landmarks = best_lm.seen;

    BenchmarkSample sample;
    sample.particle_count = particle_count;
    sample.step = step;
    sample.observations = static_cast<int>(observations.size());
    sample.resampled = filter.last_resampled;
    sample.mean_observations = static_cast<double>(observations.size());
    sample.resample_rate = filter.last_resampled ? 1.0 : 0.0;
    sample.time = static_cast<double>(step) * bench.dt;
    sample.pose_rmse = pose_error;
    sample.mean_landmark_rmse = mean_lm.rmse;
    sample.best_landmark_rmse = best_lm.rmse;
    sample.effective_n = neff;
    sample.log_weight_span = log_weight_span;
    run.samples.push_back(sample);
  }
  const auto end = std::chrono::steady_clock::now();

  if (result.samples > 0) {
    const double inv_samples = 1.0 / static_cast<double>(result.samples);
    result.mean_pose_rmse *= inv_samples;
    result.mean_landmark_rmse *= inv_samples;
    result.mean_best_landmark_rmse *= inv_samples;
    result.mean_effective_n *= inv_samples;
    result.mean_log_weight_span *= inv_samples;
  }

  result.runtime_ms =
      std::chrono::duration<double, std::milli>(end - start).count();
  report_progress(bench.steps, true);
  return run;
}

struct SeedScenario {
  SimConfig sim;
  unsigned seed = 0;
  unsigned filter_seed = 0;
  unsigned observation_seed = 0;
};

std::vector<SeedScenario> make_seed_scenarios(const SimConfig &sim,
                                              const BenchmarkConfig &bench) {
  std::vector<unsigned> seeds = bench.random_seeds;
  if (seeds.empty())
    seeds.push_back(42);

  std::vector<SeedScenario> scenarios;
  scenarios.reserve(seeds.size());

  for (unsigned seed : seeds) {
    SeedScenario scenario;
    scenario.sim = sim;
    scenario.seed = seed;
    scenario.sim.map_seed = map_seed_from_trial_seed(seed);
    scenario.filter_seed = mix_seed(seed, 0x2468ace0U);
    scenario.observation_seed = mix_seed(seed, 0xfdb97531U);
    scenarios.push_back(scenario);
  }

  return scenarios;
}

BenchmarkRun average_runs(const std::vector<BenchmarkRun> &runs) {
  BenchmarkRun aggregate;
  if (runs.empty())
    return aggregate;

  const double inv_runs = 1.0 / static_cast<double>(runs.size());
  BenchmarkResult &result = aggregate.result;
  result.particle_count = runs.front().result.particle_count;
  result.seed_runs = static_cast<int>(runs.size());
  result.steps = runs.front().result.steps;

  double resamples = 0.0;
  double samples = 0.0;
  double observations = 0.0;
  double mean_seen = 0.0;
  double best_seen = 0.0;
  for (const BenchmarkRun &run : runs) {
    const BenchmarkResult &r = run.result;
    resamples += r.resamples;
    samples += r.samples;
    observations += r.total_observations;
    result.runtime_ms += r.runtime_ms;
    result.mean_pose_rmse += r.mean_pose_rmse;
    result.final_pose_rmse += r.final_pose_rmse;
    result.max_pose_rmse += r.max_pose_rmse;
    result.mean_landmark_rmse += r.mean_landmark_rmse;
    result.final_landmark_rmse += r.final_landmark_rmse;
    result.mean_best_landmark_rmse += r.mean_best_landmark_rmse;
    result.final_best_landmark_rmse += r.final_best_landmark_rmse;
    result.mean_effective_n += r.mean_effective_n;
    result.final_effective_n += r.final_effective_n;
    result.mean_log_weight_span += r.mean_log_weight_span;
    result.final_log_weight_span += r.final_log_weight_span;
    result.max_log_weight_span += r.max_log_weight_span;
    mean_seen += r.final_mean_seen_landmarks;
    best_seen += r.final_best_seen_landmarks;
  }

  result.resamples = static_cast<int>(std::lround(resamples * inv_runs));
  result.samples = static_cast<int>(std::lround(samples * inv_runs));
  result.total_observations =
      static_cast<int>(std::lround(observations * inv_runs));
  result.runtime_ms *= inv_runs;
  result.mean_pose_rmse *= inv_runs;
  result.final_pose_rmse *= inv_runs;
  result.max_pose_rmse *= inv_runs;
  result.mean_landmark_rmse *= inv_runs;
  result.final_landmark_rmse *= inv_runs;
  result.mean_best_landmark_rmse *= inv_runs;
  result.final_best_landmark_rmse *= inv_runs;
  result.mean_effective_n *= inv_runs;
  result.final_effective_n *= inv_runs;
  result.mean_log_weight_span *= inv_runs;
  result.final_log_weight_span *= inv_runs;
  result.max_log_weight_span *= inv_runs;
  result.final_mean_seen_landmarks =
      static_cast<int>(std::lround(mean_seen * inv_runs));
  result.final_best_seen_landmarks =
      static_cast<int>(std::lround(best_seen * inv_runs));

  std::size_t sample_count = runs.front().samples.size();
  for (const BenchmarkRun &run : runs)
    sample_count = std::min(sample_count, run.samples.size());

  aggregate.samples.resize(sample_count);
  for (std::size_t i = 0; i < sample_count; ++i) {
    BenchmarkSample sample;
    sample.particle_count = result.particle_count;
    sample.step = runs.front().samples[i].step;
    sample.time = runs.front().samples[i].time;

    for (const BenchmarkRun &run : runs) {
      const BenchmarkSample &s = run.samples[i];
      sample.mean_observations += s.mean_observations;
      sample.resample_rate += s.resample_rate;
      sample.pose_rmse += s.pose_rmse;
      sample.mean_landmark_rmse += s.mean_landmark_rmse;
      sample.best_landmark_rmse += s.best_landmark_rmse;
      sample.effective_n += s.effective_n;
      sample.log_weight_span += s.log_weight_span;
    }

    sample.mean_observations *= inv_runs;
    sample.resample_rate *= inv_runs;
    sample.observations =
        static_cast<int>(std::lround(sample.mean_observations));
    sample.resampled = sample.resample_rate >= 0.5;
    sample.pose_rmse *= inv_runs;
    sample.mean_landmark_rmse *= inv_runs;
    sample.best_landmark_rmse *= inv_runs;
    sample.effective_n *= inv_runs;
    sample.log_weight_span *= inv_runs;
    aggregate.samples[i] = sample;
  }

  return aggregate;
}

void write_timeseries_csv(const std::vector<BenchmarkRun> &runs,
                          const std::string &path) {
  if (path.empty())
    return;

  std::ofstream out(path);
  if (!out)
    return;

  write_timeseries_header(out);
  out << std::setprecision(10);
  for (const BenchmarkRun &run : runs) {
    for (const BenchmarkSample &sample : run.samples) {
      out << run.result.particle_count << ',' << run.result.seed_runs << ','
          << sample.step << ',' << sample.time << ',' << sample.pose_rmse
          << ',' << sample.mean_landmark_rmse << ','
          << sample.best_landmark_rmse << ',' << sample.effective_n << ','
          << sample.log_weight_span << ',' << sample.mean_observations << ','
          << sample.resample_rate << '\n';
    }
  }
}
} // namespace

void sanitize_benchmark_config(BenchmarkConfig &config) {
  std::vector<int> valid_counts;
  valid_counts.reserve(config.particle_counts.size());
  for (int count : config.particle_counts) {
    if (count > 0)
      valid_counts.push_back(count);
  }
  config.particle_counts = std::move(valid_counts);
  config.steps = std::max(1, config.steps);
  config.metric_interval = std::max(1, config.metric_interval);
  config.dt = std::max(1e-6, config.dt);
  config.initial_std = std::max(0.0, config.initial_std);
  if (config.random_seeds.empty())
    config.random_seeds.push_back(42);
  config.figure8_period = std::max(config.dt, config.figure8_period);
  config.square_straight_steps = std::max(1, config.square_straight_steps);
  config.square_turn_steps = std::max(1, config.square_turn_steps);
}

bool load_benchmark_config(BenchmarkConfig &config, const char *path) {
  std::ifstream in(path);
  if (!in)
    return false;

  config.random_seeds.clear();
  std::string line;
  while (std::getline(in, line)) {
    const std::size_t comment = line.find('#');
    if (comment != std::string::npos)
      line = line.substr(0, comment);

    const std::size_t pos = line.find('=');
    if (pos == std::string::npos)
      continue;

    const std::string key = trim(line.substr(0, pos));
    const std::string value = trim(line.substr(pos + 1));
    try {
      if (key == "particle_counts")
        config.particle_counts = parse_int_list(value);
      else if (key == "steps")
        config.steps = std::stoi(value);
      else if (key == "metric_interval")
        config.metric_interval = std::stoi(value);
      else if (key == "dt")
        config.dt = std::stod(value);
      else if (key == "initial_std")
        config.initial_std = std::stod(value);
      else if (key == "random_seeds")
        config.random_seeds = parse_uint_list(value);
      else if (key == "filter_seed" && config.random_seeds.empty())
        config.random_seeds.push_back(static_cast<unsigned>(std::stoul(value)));
      else if (key == "motion_pattern")
        config.motion_pattern = value;
      else if (key == "figure8_period")
        config.figure8_period = std::stod(value);
      else if (key == "square_straight_steps")
        config.square_straight_steps = std::stoi(value);
      else if (key == "square_turn_steps")
        config.square_turn_steps = std::stoi(value);
      else if (key == "write_timeseries")
        config.write_timeseries = parse_bool(value);
      else if (key == "csv_path")
        config.csv_path = value;
    } catch (...) {
    }
  }

  sanitize_benchmark_config(config);
  return true;
}

bool save_benchmark_config(const BenchmarkConfig &config, const char *path) {
  BenchmarkConfig effective = config;
  sanitize_benchmark_config(effective);

  std::ofstream out(path);
  if (!out)
    return false;

  out << std::setprecision(17);
  out << "# Scenario comes from sim_config.ini. This file controls benchmark "
         "execution.\n";
  out << "particle_counts=";
  for (std::size_t i = 0; i < effective.particle_counts.size(); ++i) {
    if (i > 0)
      out << ',';
    out << effective.particle_counts[i];
  }
  out << '\n';
  out << "steps=" << effective.steps << '\n';
  out << "dt=" << effective.dt << '\n';
  out << "metric_interval=" << effective.metric_interval << '\n';
  out << "initial_std=" << effective.initial_std << '\n';
  out << "random_seeds=";
  for (std::size_t i = 0; i < effective.random_seeds.size(); ++i) {
    if (i > 0)
      out << ',';
    out << effective.random_seeds[i];
  }
  out << "\n\n";
  out << "# motion_pattern: circle, straight, spin, figure8, square\n";
  out << "motion_pattern=" << effective.motion_pattern << '\n';
  out << "figure8_period=" << effective.figure8_period << '\n';
  out << "square_straight_steps=" << effective.square_straight_steps << '\n';
  out << "square_turn_steps=" << effective.square_turn_steps << "\n\n";
  out << "write_timeseries=" << (effective.write_timeseries ? 1 : 0) << '\n';
  out << "csv_path=" << effective.csv_path << '\n';
  return true;
}

std::vector<BenchmarkRun>
run_benchmark_suite_detailed(const SimConfig &sim_config,
                             const BenchmarkConfig &bench,
                             const BenchmarkProgressCallback &progress_cb) {
  BenchmarkConfig effective = bench;
  sanitize_benchmark_config(effective);
  if (effective.particle_counts.empty())
    effective.particle_counts.push_back(sim_config.particle_count);

  const std::vector<SeedScenario> scenarios =
      make_seed_scenarios(sim_config, effective);
  const int total_runs = static_cast<int>(effective.particle_counts.size() *
                                          scenarios.size());
  const int total_steps_all = total_runs * std::max(1, effective.steps);
  if (progress_cb) {
    BenchmarkProgress progress;
    progress.total_runs = total_runs;
    progress.seed_runs = static_cast<int>(scenarios.size());
    progress.total_steps = effective.steps;
    progress.total_steps_all = total_steps_all;
    progress_cb(progress);
  }

  std::vector<BenchmarkRun> runs;
  runs.reserve(effective.particle_counts.size());
  for (int i = 0; i < static_cast<int>(effective.particle_counts.size()); ++i) {
    const int particle_count = effective.particle_counts[i];
    if (particle_count <= 0)
      continue;

    std::vector<BenchmarkRun> seed_runs;
    seed_runs.reserve(scenarios.size());
    for (int seed_i = 0; seed_i < static_cast<int>(scenarios.size()); ++seed_i) {
      const int run_index = i * static_cast<int>(scenarios.size()) + seed_i + 1;
      const int completed_steps_before = (run_index - 1) * effective.steps;
      seed_runs.push_back(run_once(
          scenarios[seed_i].sim, effective, particle_count,
          run_index, total_runs, seed_i + 1, static_cast<int>(scenarios.size()),
          scenarios[seed_i].filter_seed, scenarios[seed_i].observation_seed,
          completed_steps_before, total_steps_all, progress_cb));
    }
    runs.push_back(average_runs(seed_runs));
  }

  if (effective.write_timeseries)
    write_timeseries_csv(runs, effective.csv_path);

  if (progress_cb) {
    BenchmarkProgress progress;
    progress.total_runs = total_runs;
    progress.completed_runs = progress.total_runs;
    progress.seed_runs = static_cast<int>(scenarios.size());
    progress.total_steps = effective.steps;
    progress.step = effective.steps;
    progress.completed_steps = total_steps_all;
    progress.total_steps_all = total_steps_all;
    progress.complete = true;
    progress_cb(progress);
  }
  return runs;
}

std::vector<BenchmarkResult> run_benchmark_suite(const SimConfig &sim_config,
                                                 const BenchmarkConfig &bench) {
  const std::vector<BenchmarkRun> runs =
      run_benchmark_suite_detailed(sim_config, bench);
  std::vector<BenchmarkResult> results;
  results.reserve(runs.size());
  for (const BenchmarkRun &run : runs)
    results.push_back(run.result);
  return results;
}

void print_benchmark_summary(const std::vector<BenchmarkResult> &results) {
  std::cout << "particles,seed_runs,steps,runtime_ms,avg_resamples,"
               "mean_pose_rmse,"
               "final_pose_rmse,mean_landmark_rmse,final_landmark_rmse,"
               "mean_best_landmark_rmse,final_best_landmark_rmse,"
               "mean_effective_n_pre_resample,"
               "final_effective_n_pre_resample,mean_log_weight_span,"
               "final_log_weight_span,max_log_weight_span,mean_seen,"
               "best_seen\n";

  std::cout << std::fixed << std::setprecision(6);
  for (const BenchmarkResult &r : results) {
    std::cout << r.particle_count << ',' << r.seed_runs << ',' << r.steps
              << ',' << r.runtime_ms << ',' << r.resamples << ','
              << r.mean_pose_rmse << ','
              << r.final_pose_rmse << ',' << r.mean_landmark_rmse << ','
              << r.final_landmark_rmse << ',' << r.mean_best_landmark_rmse
              << ',' << r.final_best_landmark_rmse << ','
              << r.mean_effective_n << ',' << r.final_effective_n << ','
              << r.mean_log_weight_span << ',' << r.final_log_weight_span
              << ',' << r.max_log_weight_span << ','
              << r.final_mean_seen_landmarks << ','
              << r.final_best_seen_landmarks << '\n';
  }
}
