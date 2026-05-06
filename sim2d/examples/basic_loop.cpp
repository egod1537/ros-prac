#include "sim2d/sim.hpp"
#include "sim2d/sim_view.hpp"

#include <iostream>

int main() {
  sim2d::WorldConfig config = sim2d::make_default_world();
  config.seed = 42;

  sim2d::Simulator2D sim(config);
  sim2d::SimView view;

  view.write_header(std::cout);
  for (int i = 0; i < 40; ++i) {
    const sim2d::Control command{0.15, 0.03};
    const sim2d::StepResult result = sim.step(command);
    view.write_step(std::cout, result);
  }

  return 0;
}
