// #pragma once
// #include "sim/sim2d.hpp"
// #include <Eigen/Dense>
// #include <Eigen/src/Core/Matrix.h>
// #include <cstdint>
// #include <random>
// #include <vector>
//
// struct Particle {
//   double x, y, theta;
//   double weight;
//   double log_weight;
// };
//
// struct MCL {
//   std::vector<Particle> particles;
//   std::vector<Eigen::Vector2d> known_map;
//
//   double sigma_v, sigma_w, sigma_r, sigma_phi;
//   double max_range;
//
//   std::mt19937 rng;
//   int resample_count = 0;
//   std::vector<Particle> resample_buffer;
//   std::vector<double> cdf_buffer;
//
//   MCL() = default;
//   MCL(double sv, double sw, double sr, double sphi, uint32_t seed = 42);
//
//   void init_uniform(int M, double xmin, double xmax, double ymin, double
//   ymax);
//
//   void init_gaussian(int M, double x0, double y0, double th0, double std);
//   void predict(double dist, double dtheta);
//   void weight(const std::vector<Observation> &obs);
//   void resample();
//   void observe(const std::vector<Observation> &obs);
//
//   Pose2D mean_pose() const;
//   double effective_n() const;
//   int size() const { return particles.size(); }
// };
