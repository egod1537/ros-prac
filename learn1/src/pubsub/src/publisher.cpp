#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

using Msg = std_msgs::msg::String;

class Publisher : public rclcpp::Node {
public:
  Publisher() : Node("publisher"), count_(0) {
    pub_ = create_publisher<Msg>("topic", 10);
    timer_ = create_wall_timer(std::chrono::milliseconds(500),
                               std::bind(&Publisher::timer_callback, this));
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;

  void timer_callback() {
    auto msg = Msg();
    msg.data = "hello" + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());
    pub_->publish(msg);
  }
};
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Publisher>());
  rclcpp::shutdown();
  return 0;
}
