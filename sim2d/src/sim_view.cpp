#include "sim2d/sim_view.hpp"

#include <iomanip>
#include <ostream>
#include <sstream>

namespace sim2d {

SimView::SimView(SimViewConfig config) : config_(config) {}

void SimView::write_header(std::ostream &out) const {
  out << "record,step,time,x,y,theta,odom_translation,odom_rotation,"
         "obs_count,landmark_id,range,bearing,true_range,true_bearing\n";
}

void SimView::write_step(std::ostream &out, const StepResult &step) const {
  out << std::fixed << std::setprecision(config_.precision);
  out << "step," << step.step_index << ',' << step.time << ','
      << step.true_pose.x << ',' << step.true_pose.y << ','
      << step.true_pose.theta << ',' << step.odometry.translation << ','
      << step.odometry.rotation << ',' << step.observations.size()
      << ",,,,,\n";

  if (!config_.include_observations)
    return;

  for (const Observation &observation : step.observations) {
    out << "obs," << step.step_index << ',' << step.time << ",,,,,,"
        << step.observations.size() << ',' << observation.landmark_id << ','
        << observation.range << ',' << observation.bearing << ','
        << observation.true_range << ',' << observation.true_bearing << '\n';
  }
}

std::string SimView::format_step(const StepResult &step) const {
  std::ostringstream out;
  write_step(out, step);
  return out.str();
}

} // namespace sim2d
