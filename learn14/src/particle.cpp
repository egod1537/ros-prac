#include "particle.hpp"
#include "geom.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <cassert>
#include <cmath>

double Particle::update_landmark(int idx, double r, double phi, double sigma_r,
                                 double sigma_phi) {
  assert(is_known(idx));

  auto &lm = landmarks[idx];

  double dx = lm.mu.x() - x;
  double dy = lm.mu.y() - y;
  double q = dx * dx + dy * dy;
  double sq = std::sqrt(q);

  Eigen::Matrix2d H = Eigen::Matrix2d::Zero();

  H(0, 0) = dx / sq;
  H(0, 1) = dy / sq;
  H(1, 0) = -dy / q;
  H(1, 1) = dx / q;

  double r_hat = sq;
  double phi_hat = std::atan2(dy, dx) - theta;
  Eigen::Vector2d nu(r - r_hat, wrap(phi - phi_hat));

  Eigen::Matrix2d R;
  R << sigma_r * sigma_r, 0, 0, sigma_phi * sigma_phi;

  Eigen::Matrix2d S = H * lm.sigma * H.transpose() + R;
  Eigen::Matrix2d K = lm.sigma * H.transpose() * S.inverse();

  lm.mu = lm.mu + K * nu;

  Eigen::Matrix2d I_KH = Eigen::Matrix2d::Identity() - K * H;
  lm.sigma = I_KH * lm.sigma * I_KH.transpose() + K * R * K.transpose();
  lm.sigma = 0.5 * (lm.sigma + lm.sigma.transpose());

  for (int i = 0; i < 2; ++i)
    if (lm.sigma(i, i) < 1e-9)
      lm.sigma(i, i) = 1e-9;

  double log_w =
      -0.5 * nu.dot(S.inverse() * nu) - 0.5 * std::log(S.determinant());
  return log_w;
}

void Particle::init_landmark(int idx, double r, double phi, double sigma_r,
                             double sigma_phi) {
  ensure_capacity(idx);

  auto &lm = landmarks[idx];

  double a = theta + phi;
  double c = std::cos(a);
  double s = std::sin(a);
  lm.mu.x() = x + r * c;
  lm.mu.y() = y + r * s;

  Eigen::Matrix2d G;
  G << c, -r * s, s, r * c;

  Eigen::Matrix2d Q;
  Q << sigma_r * sigma_r, 0, 0, sigma_phi * sigma_phi;

  lm.sigma = G * Q * G.transpose();
  lm.seen = true;
}

bool Particle::is_known(int idx) const {
  return idx >= 0 && idx < (int)landmarks.size() && landmarks[idx].seen;
}
void Particle::ensure_capacity(int idx) {
  if ((int)landmarks.size() <= idx)
    landmarks.resize(idx + 1);
}
