#include "geometry_msgs/msg/transform_stamped.hpp"
#include <chrono>
#include <cmath>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <tf2_ros/transform_broadcaster.hpp>

class Mover : public rclcpp::Node {
public:
  Mover() : Node("mover") {
    broad_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);

    timer_ = create_wall_timer(std::chrono::milliseconds(50),
                               [this]() { publish_tf(); });
    RCLCPP_INFO(this->get_logger(), "mover started: odom -> base_link");
  }

private:
  void publish_tf() {
    double t = now().seconds();
    double radius = 2.0;
    double speed = 0.5;

    geometry_msgs::msg::TransformStamped tf;
    tf.header.stamp = now();
    tf.header.frame_id = "odom";
    tf.child_frame_id = "base_link";

    tf.transform.translation.x = radius * std::cos(speed * t);
    tf.transform.translation.y = radius * std::sin(speed * t);
    tf.transform.translation.z = 0.0;

    double yaw = speed * t + M_PI / 2.0;
    tf.transform.rotation.x = 0.0;
    tf.transform.rotation.y = 0.0;
    tf.transform.rotation.z = std::sin(yaw / 2.0);
    tf.transform.rotation.w = std::cos(yaw / 2.0);

    broad_->sendTransform(tf);
  }

  std::unique_ptr<tf2_ros::TransformBroadcaster> broad_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Mover>());
  rclcpp::shutdown();
  return 0;
}
