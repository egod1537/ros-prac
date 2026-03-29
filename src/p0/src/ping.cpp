#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <std_msgs/msg/detail/int32__struct.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <std_msgs/msg/int32.hpp>
#include <string>

using namespace std::chrono_literals;

class Ping : public rclcpp::Node {
public:
  Ping() : Node("ping"), index_(0) {
    publisher_ = this->create_publisher<std_msgs::msg::Int32>("ping", 10);
    subscriber_ = this->create_subscription<std_msgs::msg::Int32>(
        "pong", 10,
        std::bind(&Ping::subscribe_callback, this, std::placeholders::_1));

    timer_ =
        this->create_wall_timer(500ms, std::bind(&Ping::publish_initial, this));
  }

private:
  void subscribe_callback(const std_msgs::msg::Int32::SharedPtr msg) {
    int32_t num = msg->data;
    RCLCPP_INFO(this->get_logger(), "Received: %d, Publishing: %d", num,
                num + 1);

    delay_ = this->create_wall_timer(500ms, [this, num]() {
      if (num < 100)
        publish_message(num + 1);
      delay_->cancel();
    });
  }

  void publish_initial() {
    publish_message(index_);
    timer_->cancel();
  }

  void publish_message(int32_t num) {
    auto message = std_msgs::msg::Int32();
    message.data = num;
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr delay_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
  int32_t index_ = 0;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ping>());
  rclcpp::shutdown();
  return 0;
}
