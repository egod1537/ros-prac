#pragma once

#include "sim2d/sim.hpp"

#include <iosfwd>
#include <string>

namespace sim2d {

struct SimViewConfig {
  int precision = 4;
  bool include_observations = true;
};

class SimView {
public:
  explicit SimView(SimViewConfig config = SimViewConfig{});

  void write_header(std::ostream &out) const;
  void write_step(std::ostream &out, const StepResult &step) const;
  std::string format_step(const StepResult &step) const;

private:
  SimViewConfig config_;
};

} // namespace sim2d
