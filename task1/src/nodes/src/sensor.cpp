#include "msgs/msg/temperature.hpp"
#include <chrono>
#include <memory>
#include <msgs/msg/temperature.hpp>
#include <random>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

using MsgTemperature = msgs::msg::Temperature;
std::string to_string(const MsgTemperature &msg) {
  char buf[256];
  std::snprintf(buf, sizeof(buf), "Publish %s: [%ld] %.2f", msg.name.c_str(),
                msg.time, msg.temperature);
  return buf;
}

class Sensor : public rclcpp::Node {
public:
  Sensor() : Node("sensor"), engine_(std::random_device{}()), timeStamp_(0) {
    pub_ = create_publisher<MsgTemperature>("temperature", 10);
    timer_ = create_wall_timer(std::chrono::seconds(1),
                               std::bind(&Sensor::publish, this));
  }

private:
  void publish() {
    auto msg = MsgTemperature();
    msg.name = "sensor_a";
    msg.temperature = randf(20.0, 40.0);
    msg.time = timeStamp_++;
    RCLCPP_INFO(this->get_logger(), "%s", to_string(msg).c_str());
    pub_->publish(msg);
  }

  double randf(double l, double r) {
    return std::uniform_real_distribution<double>(l, r)(engine_);
  }

  rclcpp::Publisher<MsgTemperature>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::mt19937 engine_;
  int timeStamp_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Sensor>());
  rclcpp::shutdown();
  return 0;
}
