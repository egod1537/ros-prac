#include <chrono>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <tf2/exceptions.hpp>
#include <tf2/time.hpp>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_broadcaster.hpp>
#include <tf2_ros/transform_listener.hpp>

class Tracker : public rclcpp::Node {
public:
  Tracker() : Node("tracker") {
    buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_);

    timer_ = create_wall_timer(std::chrono::milliseconds(500),
                               [this]() { lookup(); });
    RCLCPP_INFO(this->get_logger(),
                "tracker started: looking up odom -> lidar_link");
  }

private:
  void lookup() {
    try {
      auto tf =
          buffer_->lookupTransform("odom", "lidar_link", tf2::TimePointZero);

      RCLCPP_INFO(get_logger(), "lidar in odom: x=%.2f y=%.2f z=%.2f",
                  tf.transform.translation.x, tf.transform.translation.y,
                  tf.transform.translation.z);
    } catch (const tf2::TransformException &e) {
      RCLCPP_WARN(this->get_logger(), "tf lookup failed: %s", e.what());
    }
  }

  std::unique_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Tracker>());
  rclcpp::shutdown();
  return 0;
}
