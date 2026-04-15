#include "msgs/msg/status.hpp"
#include <chrono>
#include <memory>
#include <msgs/msg/status.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

using MsgStatus = msgs::msg::Status;

class Talker : public rclcpp::Node {
public:
  Talker() : Node("talker") {
    pub_ = create_publisher<MsgStatus>("status", 10);
    timer_ = create_wall_timer(std::chrono::seconds(1),
                               std::bind(&Talker::publish, this));
  }

private:
  void publish() {
    auto msg = MsgStatus();
    msg.name = "sensor_a";
    msg.level = count_++;
    msg.message = "all good";
    RCLCPP_INFO(this->get_logger(), "[%s] level=%d: %s", msg.name.c_str(),
                msg.level, msg.message.c_str());
    pub_->publish(msg);
  }

  rclcpp::Publisher<MsgStatus>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
