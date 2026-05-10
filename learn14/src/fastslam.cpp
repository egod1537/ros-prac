#include "fastslam.hpp"
#include "geom.hpp"
#include "particle.hpp"
#include "slam_types.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <cmath>
#include <cstdint>
#include <limits>
#include <random>
#include <vector>

FastSLAM::FastSLAM(double sv, double sw, double sr, double sphi, uint32_t seed)
    : sigma_v(sv), sigma_w(sw), sigma_r(sr), sigma_phi(sphi) {
  rng = std::mt19937(seed);
}

void FastSLAM::init_gaussian(int M, double x0, double y0, double th0,
                             double std) {
  if (M <= 0)
    return;

  particles.clear();
  particles.reserve(M);

  resample_buf.clear();
  resample_buf.reserve(M);

  cdf_buf.clear();
  cdf_buf.reserve(M);

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

void FastSLAM::predict(double dist, double dtheta) {
  std::normal_distribution<double> nd(0.0, 1.0);

  for (auto &p : particles) {
    double d_i = dist + sigma_v * nd(rng);
    double th_i = dtheta + sigma_w * nd(rng);

    double mid = p.theta + 0.5 * th_i;
    p.x += d_i * std::cos(mid);
    p.y += d_i * std::sin(mid);
    p.theta = wrap(p.theta + th_i);
  }
}

void FastSLAM::resample() {
  const int M = particles.size();
  if (M <= 0)
    return;

  resample_buf.clear();
  resample_buf.reserve(M);

  cdf_buf.resize(M);
  cdf_buf[0] = particles[0].weight;
  for (int i = 1; i < M; ++i)
    cdf_buf[i] = cdf_buf[i - 1] + particles[i].weight;

  std::uniform_real_distribution<double> ud(0.0, 1.0 / M);
  double u0 = ud(rng);

  int j = 0;
  for (int i = 0; i < M; ++i) {
    double u = u0 + static_cast<double>(i) / M;
    while (j < M - 1 && cdf_buf[j] < u)
      ++j;

    resample_buf.push_back(particles[j]);
    resample_buf.back().weight = 1.0 / M;
  }

  particles.swap(resample_buf);
}

void FastSLAM::observe(const std::vector<Observation> &obs) {
  if (particles.empty())
    return;

  for (auto &p : particles) {
    double log_w = 0.0;
    for (const auto &z : obs) {
      if (z.id < 0)
        continue;
      p.ensure_capacity(z.id);

      if (p.is_known(z.id)) {
        log_w += p.update_landmark(z.id, z.r, z.phi, sigma_r, sigma_phi);
      } else {
        p.init_landmark(z.id, z.r, z.phi, sigma_r, sigma_phi);
      }
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

  if (effective_n() < 0.5 * particles.size()) {
    resample();
  }
}

Pose2D FastSLAM::mean_pose() const {
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

std::vector<Eigen::Vector2d> FastSLAM::mean_landmarks() const {
  int lm_size = 0;
  for (auto &p : particles)
    lm_size = std::max(lm_size, (int)p.landmarks.size());
  std::vector<Eigen::Vector2d> result(lm_size);

  for (int i = 0; i < lm_size; ++i) {
    Eigen::Vector2d acc = Eigen::Vector2d::Zero();
    double w_sum = 0.0;
    for (const auto &p : particles) {
      if (i >= (int)p.landmarks.size())
        continue;
      auto &lm = p.landmarks[i];
      if (!lm.seen)
        continue;

      acc += p.weight * lm.mu;
      w_sum += p.weight;
    }

    result[i] = (w_sum > 0) ? (acc / w_sum).eval() : Eigen::Vector2d::Zero();
  }

  return result;
}

double FastSLAM::effective_n() const {
  double s = 0.0;
  for (const auto &p : particles)
    s += p.weight * p.weight;
  if (s <= 0.0)
    return 0.0;
  return 1.0 / s;
}
