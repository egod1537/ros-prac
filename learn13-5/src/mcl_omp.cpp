#include "mcl_omp.hpp"
#include "geom.hpp"
#include "omp.h"
#include "sim2d.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <random>
#include <vector>

MCL_OMP::MCL_OMP(double sv, double sw, double sr, double sphi,
                 std::uint32_t seed)
    : sigma_v(sv), sigma_w(sw), sigma_r(sr), sigma_phi(sphi), rng(seed) {
  int n = omp_get_max_threads();
  thread_rngs.reserve(n);
  for (int i = 0; i < n; ++i) {
    thread_rngs.emplace_back(rng() ^ (i * 0x9E3779B9u));
  }
}

void MCL_OMP::init_uniform(int M, double xmin, double xmax, double ymin,
                           double ymax) {
  if (M <= 0)
    return;

  particles.clear();
  particles.reserve(M);

  resample_buffer.clear();
  resample_buffer.reserve(M);

  cdf_buffer.clear();
  cdf_buffer.reserve(M);

  resample_count = 0;

  std::uniform_real_distribution<double> ux(xmin, xmax);
  std::uniform_real_distribution<double> uy(ymin, ymax);
  std::uniform_real_distribution<double> ut(-M_PI, M_PI);
  const double inv_M = 1.0 / M;

  for (int i = 0; i < M; ++i) {
    Particle p;
    p.x = ux(rng);
    p.y = uy(rng);
    p.theta = ut(rng);
    p.weight = inv_M;
    p.log_weight = 0.0;
    particles.push_back(p);
  }
}

void MCL_OMP::init_gaussian(int M, double x0, double y0, double th0,
                            double std) {
  if (M <= 0)
    return;

  particles.clear();
  particles.reserve(M);

  resample_buffer.clear();
  resample_buffer.reserve(M);

  cdf_buffer.clear();
  cdf_buffer.reserve(M);

  resample_count = 0;

  std::normal_distribution<double> nd(0.0, 1.0);
  const double inv_M = 1.0 / M;

  for (int i = 0; i < M; ++i) {
    Particle p;
    p.x = x0 + std * nd(rng);
    p.y = y0 + std * nd(rng);
    p.theta = wrap(th0 + std * nd(rng));
    p.weight = inv_M;
    p.log_weight = 0.0;
    particles.push_back(p);
  }
}

void MCL_OMP::predict(double dist, double dtheta) {
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    auto &local_rng = thread_rngs[tid];
    std::normal_distribution<double> nd(0.0, 1.0);

#pragma omp for
    for (int i = 0; i < (int)particles.size(); ++i) {
      auto &p = particles[i];
      double d_i = dist + sigma_v * nd(local_rng);
      double th_i = dtheta + sigma_w * nd(local_rng);

      double mid = p.theta + 0.5 * th_i;
      p.x += d_i * std::cos(mid);
      p.y += d_i * std::sin(mid);
      p.theta = wrap(p.theta + th_i);
    }
  }
}

void MCL_OMP::weight(const std::vector<Observation> &obs) {
  if (particles.empty())
    return;

  int sz = (int)particles.size();
#pragma omp parallel for
  for (int i = 0; i < sz; ++i) {
    auto &p = particles[i];
    double log_w = 0.0;
    for (const auto &z : obs) {
      if (z.id < 0 || static_cast<std::size_t>(z.id) >= known_map.size())
        continue;
      auto &lm = known_map[z.id];

      double dx = lm.x() - p.x;
      double dy = lm.y() - p.y;

      double r_hat = std::hypot(dx, dy);
      double phi_hat = wrap(std::atan2(dy, dx) - p.theta);

      double dr = z.r - r_hat;
      double dphi = wrap(z.phi - phi_hat);

      log_w -= 0.5 * (dr * dr / (sigma_r * sigma_r) +
                      dphi * dphi / (sigma_phi * sigma_phi));
    }
    p.log_weight = log_w;
  }

  double max_log = -std::numeric_limits<double>::infinity();
  for (const auto &p : particles)
    max_log = std::max(max_log, p.log_weight);

  double sum = 0.0;
  for (auto &p : particles) {
    p.weight = std::exp(p.log_weight - max_log);
    sum += p.weight;
  }

  if (sum > 0.0) {
    for (auto &p : particles)
      p.weight /= sum;
  } else {
    double uniform = 1.0 / particles.size();
    for (auto &p : particles)
      p.weight = uniform;
  }
}

void MCL_OMP::resample() {
  const int M = particles.size();
  if (M <= 0)
    return;

  resample_buffer.clear();
  cdf_buffer.resize(M);

#pragma omp parallel for
  for (int i = 0; i < M; ++i) {
    cdf_buffer[i] = particles[i].weight;
  }

  for (int d = 1; d < M; d <<= 1) {
    std::vector<double> next = cdf_buffer;
#pragma omp parallel for
    for (int i = d; i < M; ++i) {
      next[i] = cdf_buffer[i] + cdf_buffer[i - d];
    }
    cdf_buffer.swap(next);
  }

  std::uniform_real_distribution<double> ud(0.0, 1.0 / M);
  double u0 = ud(rng);

  resample_buffer.resize(M);
#pragma omp parallel for
  for (int i = 0; i < M; ++i) {
    double u = u0 + double(i) / M;
    int j = std::lower_bound(cdf_buffer.begin(), cdf_buffer.end(), u) -
            cdf_buffer.begin();

    if (j >= M)
      j = M - 1;
    resample_buffer[i] = particles[j];
    resample_buffer[i].weight = 1.0 / M;
  }

  particles.swap(resample_buffer);
  ++resample_count;
}

void MCL_OMP::observe(const std::vector<Observation> &obs) {
  weight(obs);
  if (effective_n() < 0.5 * particles.size()) {
    resample();
  }
}

Pose2D MCL_OMP::mean_pose() const {
  double mx = 0.0, my = 0.0;
  double mc = 0.0, ms = 0.0;
  double w_sum = 0.0;

  for (const auto &p : particles) {
    mx += p.weight * p.x;
    my += p.weight * p.y;
    mc += p.weight * std::cos(p.theta);
    ms += p.weight * std::sin(p.theta);
    w_sum += p.weight;
  }

  Pose2D result;
  if (w_sum > 0.0) {
    result.x = mx / w_sum;
    result.y = my / w_sum;
    result.theta = std::atan2(ms, mc);
  } else {
    result.x = result.y = result.theta = 0.0;
  }
  return result;
}

double MCL_OMP::effective_n() const {
  double s = 0.0;
  for (const auto &p : particles)
    s += p.weight * p.weight;
  if (s <= 0.0)
    return 0.0;
  return 1.0 / s;
}
