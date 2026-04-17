#include "msgs/msg/temperature.hpp"
#include <chrono>
#include <memory>
#include <msgs/msg/temperature.hpp>
#include <random>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

using MsgTemperature = msgs::msg::Temperature;

class Talker : public rclcpp::Node {
public:
  Talker() : Node("talker") {
    declare_parameter("period_ms", 1000);
    declare_parameter("unit", "celsius");

    int period = get_parameter("period_ms").as_int();
    unit_ = get_parameter("unit").as_string();

    pub_ = create_publisher<MsgTemperature>("Temperature", 10);
    timer_ = create_wall_timer(std::chrono::milliseconds(period),
                               [this]() { publish(); });
  }

private:
  void publish() {
    MsgTemperature msg;
    msg.value = 20.0 + dist_(gen_);
    msg.unit = unit_;
    RCLCPP_INFO(this->get_logger(), "pub: %.1f %s", msg.value,
                msg.unit.c_str());
    pub_->publish(msg);
  }

  rclcpp::Publisher<MsgTemperature>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  std::string unit_;
  std::mt19937 gen_{std::random_device{}()};
  std::uniform_real_distribution<> dist_{-5.0, 5.0};
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
