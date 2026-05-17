#include "learn15/mcl.hpp"
#include "learn15/geom.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <random>
#include <vector>

MCL::MCL(double sv, double sw, double sr, double sphi, uint32_t seed)
    : sigma_v(sv), sigma_w(sw), sigma_r(sr), sigma_phi(sphi), rng(seed) {}

// public
void MCL::init_gaussian(int M, double x0, double y0, double th0, double std) {
  if (M <= 0)
    return;

  particles.clear();
  particles.reserve(M);

  std::normal_distribution<double> nd(0.0, 1.0);
  const double inv_M = 1.0 / M;

  for (int i = 0; i < M; i++) {
    Particle p;
    p.x = x0 + std * nd(rng);
    p.y = y0 + std * nd(rng);
    p.theta = wrap(th0 + std * nd(rng));
    p.weight = inv_M;
    p.log_weight = 0.0;
    particles.push_back(p);
  }
}

void MCL::predict(double dist, double dtheta) {
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

void MCL::observe(const std::vector<Observation> &obs) {
  weight(obs);
  if (effective_n() < 0.5 * get_particle_count())
    resample();
}

// private
void MCL::weight(const std::vector<Observation> &obs) {
  const double inv_r2 = 1.0 / (sigma_r * sigma_r);
  const double inv_phi2 = 1.0 / (sigma_phi * sigma_phi);

  for (auto &p : particles) {
    double log_w = 0.0;

    for (auto &z : obs) {
      if (z.id < 0 || z.id >= known_maps.size())
        continue;

      auto &lm = known_maps[z.id];
      double dx = lm.x() - p.x;
      double dy = lm.y() - p.y;
      double q = dx * dx + dy * dy;

      double r_hat = std::sqrt(q);
      double phi_hat = std::atan2(dy, dx) - p.theta;

      double dr = z.r - r_hat;
      double dphi = wrap(z.phi - phi_hat);
      log_w += -0.5 * (dr * dr * inv_r2 + dphi * dphi * inv_phi2);
    }

    p.log_weight += log_w;
  }

  double log_max = -std::numeric_limits<double>::infinity();
  for (auto &p : particles)
    log_max = std::max(log_max, p.log_weight);

  double sum_exp = 0.0;
  for (auto &p : particles) {
    sum_exp += std::exp(p.log_weight - log_max);
  }
  double lse = log_max + std::log(sum_exp);

  for (auto &p : particles) {
    p.log_weight -= lse;
    p.weight = std::exp(p.log_weight);
  }
}
void MCL::resample() {
  int M = get_particle_count();

  std::vector<double> cdf(M);
  cdf[0] = particles[0].weight;
  for (int i = 1; i < M; i++)
    cdf[i] = cdf[i - 1] + particles[i].weight;

  std::uniform_real_distribution<double> ud(0.0, 1.0 / M);
  double u0 = ud(rng);

  std::vector<Particle> resample_buf;
  resample_buf.reserve(M);
  for (int i = 0; i < M; i++) {
    double u = u0 + static_cast<double>(i) / M;
    int idx = std::lower_bound(cdf.begin(), cdf.end(), u) - cdf.begin();
    if (idx == M)
      idx = M - 1;
    resample_buf.push_back(particles[idx]);
  }

  std::swap(particles, resample_buf);

  double init_log_w = -std::log(M);
  for (auto &p : particles) {
    p.log_weight = init_log_w;
    p.weight = 1.0 / M;
  }
}

Pose2D MCL::mean_pose() const {
  Pose2D result{0.0, 0.0, 0.0};

  double sum_s = 0.0, sum_c = 0.0;

  for (auto &p : particles) {
    result.x += p.weight * p.x;
    result.y += p.weight * p.y;
    sum_s += p.weight * std::sin(p.theta);
    sum_c += p.weight * std::cos(p.theta);
  }

  result.theta = std::atan2(sum_s, sum_c);

  return result;
}
double MCL::effective_n() const {
  double sum = 0.0;
  for (auto &p : particles) {
    sum += p.weight * p.weight;
  }
  if (sum > 0.0)
    return 1.0 / sum;
  return 0.0;
}
