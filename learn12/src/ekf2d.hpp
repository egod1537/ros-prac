#pragma once
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

struct EKF2D {
  Eigen::VectorXd x;
  Eigen::MatrixXd P;

  int n;

  double sigma_v, sigma_w;
  double sigma_r, sigma_phi;

  double max_range;

  EKF2D() = default;
  EKF2D(double sv, double sw, double sr, double sphi);

  void predict(double dist, double dtheta);
  void update(int landmark_idx, double r, double phi);
  void add_landmark(double r, double phi);

  void observe(int idx, double r, double phi);

  int get_landmark_count() const { return (n - 3) / 2; }
  bool is_seen(int idx) const { return idx < get_landmark_count(); }
};
