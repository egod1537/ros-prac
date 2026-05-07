#pragma once

#include "sim2d.hpp"

namespace sim_config {
inline constexpr char kDefaultConfigPath[] = "sim_config.ini";
inline constexpr double kSigmaMin = 0.01;
inline constexpr double kSigmaMax = 0.5;
inline constexpr double kMaxRangeMin = 1.0;
inline constexpr double kMaxRangeMax = 15.0;
inline constexpr double kFovHalfMin = 0.1;
inline constexpr double kFovHalfMax = 3.14159265358979323846;
inline constexpr int kLandmarkCountMin = 0;
inline constexpr int kLandmarkCountMax = 100;
inline constexpr double kLandmarkRangeMin = -20.0;
inline constexpr double kLandmarkRangeMax = 20.0;

void sanitize(SimConfig &config);
void load(SimConfig &config, const char *path = kDefaultConfigPath);
void save(const SimConfig &config, const char *path = kDefaultConfigPath);
} // namespace sim_config
