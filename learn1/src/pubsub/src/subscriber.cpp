#include "std_msgs/msg/string.hpp"
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>

using Msg = std_msgs::msg::String;

class Subscriber : public rclcpp::Node {
public:
  Subscriber() : Node("subscriber") {
    sub_ = create_subscription<Msg>(
        "topic", 10,
        std::bind(&Subscriber::callback, this, std::placeholders::_1));
  }

private:
  void callback(const Msg::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
  }

  rclcpp::Subscription<Msg>::SharedPtr sub_;
};
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Subscriber>());
  rclcpp::shutdown();
  return 0;
}
