#pragma once
#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
#include <unordered_map>
#include <vector>

struct Timer {
  using clock = std::chrono::steady_clock;
  clock::time_point t0;
  void start() { t0 = clock::now(); }
  double stop_ms() {
    return std::chrono::duration<double, std::milli>(clock::now() - t0).count();
  }
};

struct TimingStats {
  std::unordered_map<std::string, std::vector<double>> samples;

  void record(const std::string &key, double ms) { samples[key].push_back(ms); }

  void print(int warmup = 5) const;
};
