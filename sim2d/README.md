# sim2d

Standalone 2D landmark simulation code extracted from the `learn12` idea, but
without EKF, GUI, ROS, or Eigen dependencies.

The simulator owns only the world truth:

- robot pose
- landmark map
- range/bearing sensor model
- noisy odometry sampling
- deterministic seeding for repeatable experiments

The code is split into two layers:

- `sim`: pure simulation state, motion, odometry noise, and sensor observation
- `sim_view`: formatting/output helpers for inspecting simulation results

Learning or estimation code should live outside this folder and consume
`StepResult`.

```cpp
#include "sim2d/sim.hpp"

sim2d::Simulator2D sim(sim2d::make_default_world());

auto step = sim.step({0.10, 0.02});

estimator.predict(step.odometry.translation, step.odometry.rotation);
for (const sim2d::Observation& obs : step.observations) {
  estimator.observe(obs.landmark_id, obs.range, obs.bearing);
}
```

## Build

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Run the copy-paste style example:

```sh
./build/sim2d_basic
```

## Model

`Control` is a per-step delta command: move forward by `translation`, then rotate
by `rotation`.

The true pose is updated with the command directly. The returned `odometry` is
the same command plus odometry noise, matching the shape used in `learn12`: a
consumer predicts from noisy odometry while observations come from the simulated
world.

`Observation::range` and `Observation::bearing` are noisy measurements.
`true_range` and `true_bearing` are included for logging and debugging; learned
code can ignore them.
