#include "msgs/msg/status.hpp"
#include <functional>
#include <memory>
#include <msgs/msg/status.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/utilities.hpp>

using MsgStatus = msgs::msg::Status;

class Listener : public rclcpp::Node {
public:
  Listener() : Node("listener") {
    sub_ = create_subscription<MsgStatus>(
        "status", 10,
        std::bind(&Listener::callback, this, std::placeholders::_1));
  }

private:
  void callback(const MsgStatus::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "[%s] level=%d: %s", msg->name.c_str(),
                msg->level, msg->message.c_str());
  }

  rclcpp::Subscription<MsgStatus>::SharedPtr sub_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
