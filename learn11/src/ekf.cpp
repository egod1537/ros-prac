#include "ekf.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <iostream>
#include <system_error>

EKF::EKF(double sigma_u, double sigma_z)
    : x(1), n(1), sigma_u(sigma_u), sigma_z(sigma_z) {
  x.setZero();
  P = Eigen::MatrixXd::Zero(n, n);
}

void EKF::predict(double u) {
  x(0) += u;
  P(0, 0) += sigma_u * sigma_u;
}

void EKF::update(int landmark_idx, double z) {
  Eigen::RowVectorXd H(n);
  H.setZero();
  H[0] = -1.0;
  H[landmark_idx + 1] = 1.0;

  double S = (H * P * H.transpose())(0, 0) + sigma_z * sigma_z;
  Eigen::VectorXd K = P * H.transpose() / S;

  x += K * (z - H * x);

  int dim = x.size();
  Eigen::MatrixXd I_KH = Eigen::MatrixXd::Identity(dim, dim) - K * H;
  // joseph form
  P = I_KH * P * I_KH.transpose() + K * sigma_z * sigma_z * K.transpose();

  P = 0.5 * (P + P.transpose());

  for (int i = 0; i < n; i++) {
    if (P(i, i) < 1e-9)
      P(i, i) = 1e-9;
  }
}

void EKF::add_landmark(double z) {
  int old_n = n;
  int new_n = n + 1;

  Eigen::MatrixXd P_new = Eigen::MatrixXd::Zero(new_n, new_n);
  P_new.topLeftCorner(old_n, old_n) = P; // 기존 부분 복사
  P_new(old_n, old_n) = P(0, 0) + sigma_z * sigma_z;
  P_new(0, old_n) = P(0, 0);
  P_new(old_n, 0) = P(0, 0);
  P = P_new;

  Eigen::VectorXd x_new(new_n);
  x_new.head(old_n) = x;
  x_new(old_n) = x(0) + z;
  x = x_new;

  n = new_n;
}

void EKF::observe(int idx, double z) {
  if (idx >= get_landmark_count())
    add_landmark(z);
  else
    update(idx, z);
}
