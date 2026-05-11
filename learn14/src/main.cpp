#include "sim_view.hpp"

#include <cstdio>

int main() {
  SimView sim;
  if (!sim.init()) {
    std::fprintf(stderr, "SimView init failed\n");
    return 1;
  }

  sim.run();
  return 0;
}
