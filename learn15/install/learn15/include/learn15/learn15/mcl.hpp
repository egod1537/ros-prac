#include "slam_types.hpp"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include <cstdint>
#include <random>
#include <vector>

class MCL {
public:
  double max_range;

  MCL() = default;
  MCL(double sv, double sw, double sr, double sphi, uint32_t seed = 42);

  void init_gaussian(int M, double x0, double y0, double th, double std);

  void predict(double dist, double dtheta);
  void observe(const std::vector<Observation> &obs);

  Pose2D mean_pose() const;
  int get_particle_count() const { return particles.size(); }
  const Particle &get_particle(int idx) const { return particles[idx]; }

private:
  std::vector<Particle> particles;
  std::vector<Eigen::Vector2d> known_maps;

  std::mt19937 rng;
  double sigma_v, sigma_w, sigma_r, sigma_phi;

  void weight(const std::vector<Observation> &obs);
  void resample();

  double effective_n() const;
};
