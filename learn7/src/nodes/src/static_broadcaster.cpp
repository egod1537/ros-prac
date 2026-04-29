#include "geometry_msgs/msg/transform_stamped.hpp"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>
#include <tf2_ros/static_transform_broadcaster.hpp>

class StaticBroadcaster : public rclcpp::Node {
public:
  StaticBroadcaster() : Node("static_broadcaster") {
    broad_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

    geometry_msgs::msg::TransformStamped t;
    t.header.stamp = now();
    t.header.frame_id = "base_link";
    t.child_frame_id = "lidar_link";

    t.transform.translation.x = 0.1;
    t.transform.translation.y = 0.0;
    t.transform.translation.z = 0.3;

    t.transform.rotation.x = 0.0;
    t.transform.rotation.y = 0.0;
    t.transform.rotation.z = 0.0;
    t.transform.rotation.w = 1.0;

    broad_->sendTransform(t);
    RCLCPP_INFO(this->get_logger(), "static tf: base_link -> lidar_link");
  }

private:
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broad_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StaticBroadcaster>());
  rclcpp::shutdown();
  return 0;
}
