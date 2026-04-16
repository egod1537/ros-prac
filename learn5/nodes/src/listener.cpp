#include "msgs/msg/temperature.hpp"
#include <memory>
#include <msgs/msg/temperature.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/utilities.hpp>

using MsgTemperature = msgs::msg::Temperature;

class Listener : public rclcpp::Node {
public:
  Listener() : Node("listener") {
    declare_parameter("warn_above", 24.0);
    threshold_ = get_parameter("warn_above").as_double();

    sub_ = create_subscription<MsgTemperature>(
        "temperature", 10,
        [this](MsgTemperature::SharedPtr msg) { callback(msg); });

    RCLCPP_INFO(get_logger(), "listener started: warn_above=%.1f", threshold_);
  }

private:
  void callback(MsgTemperature::SharedPtr msg) {
    if (msg->value > threshold_) {
      RCLCPP_WARN(get_logger(), "HIGH: %.1f %s", msg->value, msg->unit.c_str());
    } else {
      RCLCPP_INFO(get_logger(), "ok: %.1f %s", msg->value, msg->unit.c_str());
    }
  }

  rclcpp::Subscription<MsgTemperature>::SharedPtr sub_;
  double threshold_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
