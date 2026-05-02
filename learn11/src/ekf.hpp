#pragma once
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

struct EKF {
  Eigen::VectorXd x;
  Eigen::MatrixXd P;

  int n;

  double sigma_u;
  double sigma_z;

  EKF() = default;
  EKF(double sigma_u, double sigma_z);

  void predict(double u);
  void update(int landmark_idx, double z);
  void add_landmark(double z);

  void observe(int idx, double z);

  double robot() const { return x(0); }
  double robot_var() const { return P(0, 0); }
  double landmark(int i) const { return x(1 + i); }
  double landmark_var(int i) const { return P(1 + i, 1 + i); }

  int get_landmark_count() const { return n - 1; }
  bool is_seen(int idx) const { return idx + 1 < n; }

private:
  double &P_(int r, int c) { return P(r, c); }
  const double &P_(int r, int c) const { return P(r, c); }
};
