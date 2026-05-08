#include "timing.hpp"
#include <algorithm>
#include <numeric>

void TimingStats::print(int warmup) const {
  printf("%-12s %6s %10s %10s %10s %10s %10s\n", "key", "n", "mean", "median",
         "p95", "min", "max");
  printf("%-12s %6s %10s %10s %10s %10s %10s\n", "------------", "------",
         "----------", "----------", "----------", "----------", "----------");

  for (auto &[key, v] : samples) {
    if ((int)v.size() <= warmup)
      continue;

    auto vec = std::vector<double>(v.begin() + warmup, v.end());

    int n = vec.size();
    size_t mid = n / 2;
    size_t p95 = (size_t)(n * 0.95);

    std::nth_element(vec.begin(), vec.begin() + mid, vec.end());
    double median = vec[mid];
    std::nth_element(vec.begin(), vec.begin() + p95, vec.end());
    double p95_val = vec[p95];

    auto [mn, mx] = std::minmax_element(vec.begin(), vec.end());
    double min = *mn;
    double max = *mx;
    double mean = std::accumulate(vec.begin(), vec.end(), 0.0) / n;

    printf("%-12s %6d %10.3f %10.3f %10.3f %10.3f %10.3f\n", key.c_str(), n,
           mean, median, p95_val, min, max);
  }
}
