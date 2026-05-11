#include "sim_config.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>

namespace {
bool parse_bool(const std::string &value) {
  return value == "1" || value == "true" || value == "TRUE" ||
         value == "yes" || value == "YES" || value == "on" ||
         value == "ON";
}

void assign_config_value(SimConfig &config, const std::string &key,
                         const std::string &value) {
  try {
    if (key == "particle_count")
      config.particle_count = std::stoi(value);
    else if (key == "linear_speed")
      config.linear_speed = std::stod(value);
    else if (key == "angular_speed")
      config.angular_speed = std::stod(value);
    else if (key == "sigma_v")
      config.sigma_v = std::stod(value);
    else if (key == "sigma_w")
      config.sigma_w = std::stod(value);
    else if (key == "max_range")
      config.max_range = std::stod(value);
    else if (key == "fov_half")
      config.fov_half = std::stod(value);
    else if (key == "sigma_r")
      config.sigma_r = std::stod(value);
    else if (key == "sigma_phi")
      config.sigma_phi = std::stod(value);
    else if (key == "landmark_count")
      config.landmark_count = std::stoi(value);
    else if (key == "map_seed")
      config.map_seed = std::stoi(value);
    else if (key == "landmark_min_x")
      config.landmark_min_x = std::stod(value);
    else if (key == "landmark_max_x")
      config.landmark_max_x = std::stod(value);
    else if (key == "landmark_min_y")
      config.landmark_min_y = std::stod(value);
    else if (key == "landmark_max_y")
      config.landmark_max_y = std::stod(value);
    else if (key == "show_particles")
      config.show_particles = parse_bool(value);
    else if (key == "show_fov")
      config.show_fov = parse_bool(value);
    else if (key == "show_ellipses")
      config.show_ellipses = parse_bool(value);
    else if (key == "show_mean_landmarks")
      config.show_mean_landmarks = parse_bool(value);
    else if (key == "show_best_particle_map")
      config.show_best_particle_map = parse_bool(value);
  } catch (...) {
  }
}
} // namespace

namespace sim_config {
void sanitize(SimConfig &config) {
  config.particle_count =
      std::clamp(config.particle_count, kParticleCountMin, kParticleCountMax);
  config.linear_speed =
      std::clamp(config.linear_speed, kLinearSpeedMin, kLinearSpeedMax);
  config.angular_speed =
      std::clamp(config.angular_speed, kAngularSpeedMin, kAngularSpeedMax);
  config.sigma_v = std::clamp(config.sigma_v, kSigmaMin, kSigmaMax);
  config.sigma_w = std::clamp(config.sigma_w, kSigmaMin, kSigmaMax);
  config.sigma_r = std::clamp(config.sigma_r, kSigmaMin, kSigmaMax);
  config.sigma_phi = std::clamp(config.sigma_phi, kSigmaMin, kSigmaMax);
  config.max_range =
      std::clamp(config.max_range, kMaxRangeMin, kMaxRangeMax);
  config.fov_half = std::clamp(config.fov_half, kFovHalfMin, kFovHalfMax);
  config.landmark_count =
      std::clamp(config.landmark_count, kLandmarkCountMin, kLandmarkCountMax);
  config.map_seed = std::clamp(config.map_seed, kMapSeedMin, kMapSeedMax);
  config.landmark_min_x =
      std::clamp(config.landmark_min_x, kLandmarkRangeMin, kLandmarkRangeMax);
  config.landmark_max_x =
      std::clamp(config.landmark_max_x, kLandmarkRangeMin, kLandmarkRangeMax);
  config.landmark_min_y =
      std::clamp(config.landmark_min_y, kLandmarkRangeMin, kLandmarkRangeMax);
  config.landmark_max_y =
      std::clamp(config.landmark_max_y, kLandmarkRangeMin, kLandmarkRangeMax);

  if (config.landmark_min_x > config.landmark_max_x)
    std::swap(config.landmark_min_x, config.landmark_max_x);
  if (config.landmark_min_y > config.landmark_max_y)
    std::swap(config.landmark_min_y, config.landmark_max_y);
}

void load(SimConfig &config, const char *path) {
  std::ifstream in(path);
  if (!in)
    return;

  std::string line;
  while (std::getline(in, line)) {
    const std::size_t pos = line.find('=');
    if (pos == std::string::npos)
      continue;
    assign_config_value(config, line.substr(0, pos), line.substr(pos + 1));
  }
  sanitize(config);
}

void save(const SimConfig &config, const char *path) {
  std::ofstream out(path);
  if (!out)
    return;

  out << std::setprecision(17);
  out << "particle_count=" << config.particle_count << '\n';
  out << "linear_speed=" << config.linear_speed << '\n';
  out << "angular_speed=" << config.angular_speed << '\n';
  out << "sigma_v=" << config.sigma_v << '\n';
  out << "sigma_w=" << config.sigma_w << '\n';
  out << "max_range=" << config.max_range << '\n';
  out << "fov_half=" << config.fov_half << '\n';
  out << "sigma_r=" << config.sigma_r << '\n';
  out << "sigma_phi=" << config.sigma_phi << '\n';
  out << "landmark_count=" << config.landmark_count << '\n';
  out << "map_seed=" << config.map_seed << '\n';
  out << "landmark_min_x=" << config.landmark_min_x << '\n';
  out << "landmark_max_x=" << config.landmark_max_x << '\n';
  out << "landmark_min_y=" << config.landmark_min_y << '\n';
  out << "landmark_max_y=" << config.landmark_max_y << '\n';
  out << "show_particles=" << (config.show_particles ? 1 : 0) << '\n';
  out << "show_fov=" << (config.show_fov ? 1 : 0) << '\n';
  out << "show_ellipses=" << (config.show_ellipses ? 1 : 0) << '\n';
  out << "show_mean_landmarks=" << (config.show_mean_landmarks ? 1 : 0)
      << '\n';
  out << "show_best_particle_map=" << (config.show_best_particle_map ? 1 : 0)
      << '\n';
}
} // namespace sim_config
