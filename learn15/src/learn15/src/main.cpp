#include "mcl.hpp"

#include <iostream>

int main() {
  MCL mcl(0.05, 0.02, 0.1, 0.05, /*seed=*/42);
  mcl.init_gaussian(/*M=*/500, 0.0, 0.0, 0.0, 0.1);
  mcl.predict(/*dist=*/1.0, /*dtheta=*/0.1);

  std::cout << "learn15 MCL core initialized\n";

  return 0;
}
