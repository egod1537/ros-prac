#include "mcl.hpp"
#include "geom.hpp"
#include <cstdint>
#include <random>

MCL::MCL(double sv, double sw, double sr, double sphi, uint32_t seed)
    : sigma_v(sv), sigma_w(sw), sigma_r(sr), sigma_phi(sphi), rng(seed) {}

// public
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
