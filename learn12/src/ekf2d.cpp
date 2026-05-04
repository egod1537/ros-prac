#include "ekf2d.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <cmath>

#include "geom.hpp"

EKF2D::EKF2D(double sv, double sw, double sr, double sphi)
    : x(3), n(3), sigma_v(sv), sigma_w(sw), sigma_r(sr), sigma_phi(sphi) {
  x.setZero();
  P = Eigen::MatrixXd::Zero(n, n);
}

void EKF2D::predict(double dist, double dtheta) {
  double theta = x(RT);
  double dx = dist * cos(theta);
  double dy = dist * sin(theta);

  x(RX) += dx;
  x(RY) += dy;
  x(RT) = wrap(theta + dtheta);

  Eigen::MatrixXd G = Eigen::MatrixXd::Identity(n, n);
  G(RX, RT) = -dy;
  G(RY, RT) = dx;

  P = G * P * G.transpose();
  P(RX, RX) += sigma_v * sigma_v;
  P(RY, RY) += sigma_v * sigma_v;
  P(RT, RT) += sigma_w * sigma_w;
}

void EKF2D::update(int li, double r, double phi) {
  double dx = x(LX(li)) - x(RX);
  double dy = x(LY(li)) - x(RY);
  double q = dx * dx + dy * dy;
  double sq = std::sqrt(q);

  Eigen::MatrixXd H = Eigen::MatrixXd::Zero(2, n);

  H(0, RX) = -dx / sq;
  H(0, RY) = -dy / sq;
  H(0, LX(li)) = dx / sq;
  H(0, LY(li)) = dy / sq;

  H(1, RX) = dy / q;
  H(1, RY) = -dx / q;
  H(1, RT) = -1;
  H(1, LX(li)) = -dy / q;
  H(1, LY(li)) = dx / q;

  Eigen::Vector2d z(r, phi);
  Eigen::Vector2d z_hat(sq, wrap(std::atan2(dy, dx) - x(RT)));
  Eigen::Vector2d nu = z - z_hat;
  nu(1) = wrap(nu(1));

  Eigen::Matrix2d R;
  R << sigma_r * sigma_r, 0, 0, sigma_phi * sigma_phi;

  Eigen::MatrixXd S = H * P * H.transpose() + R;
  Eigen::MatrixXd K = P * H.transpose() * S.inverse();

  x = x + K * nu;
  x(RT) = wrap(x(RT));

  Eigen::MatrixXd I_KH = Eigen::MatrixXd::Identity(n, n) - K * H;
  P = I_KH * P * I_KH.transpose() + K * R * K.transpose();
  P = 0.5 * (P + P.transpose());
}

void EKF2D::add_landmark(double r, double phi) {
  int old_n = n;
  int new_n = n + 2;

  double s = std::sin(x(RT) + phi);
  double c = std::cos(x(RT) + phi);

  Eigen::Matrix<double, 2, 3> J_xr;
  J_xr << 1, 0, -r * s, 0, 1, r * c;

  Eigen::Matrix<double, 2, 2> J_z;
  J_z << c, -r * s, s, r * c;

  Eigen::Matrix2d R;
  R << sigma_r * sigma_r, 0, 0, sigma_phi * sigma_phi;

  Eigen::VectorXd x_new(new_n);
  x_new.head(old_n) = x;
  x_new(old_n) = x(RX) + r * c;
  x_new(old_n + 1) = x(RY) + r * s;

  Eigen::Matrix3d P_rr = P.block<3, 3>(0, 0);
  Eigen::MatrixXd P_xr = P.block(0, 0, old_n, 3);

  Eigen::MatrixXd P_new = Eigen::MatrixXd::Zero(new_n, new_n);
  P_new.topLeftCorner(old_n, old_n) = P;
  P_new.topRightCorner(old_n, 2) = P_xr * J_xr.transpose();
  P_new.bottomLeftCorner(2, old_n) = J_xr * P_xr.transpose();
  P_new.bottomRightCorner(2, 2) =
      J_xr * P_rr * J_xr.transpose() + J_z * R * J_z.transpose();

  x = x_new;
  P = P_new;
  n = new_n;
}

void EKF2D::observe(int idx, double r, double phi) {
  if (idx >= get_landmark_count())
    add_landmark(r, phi);
  else
    update(idx, r, phi);
}
