#include <cstdint>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/utilities.hpp>
#include <std_msgs/msg/int32.hpp>

using namespace std::chrono_literals;
class Pong : public rclcpp::Node {
public:
  Pong() : Node("pong") {
    publisher_ = this->create_publisher<std_msgs::msg::Int32>("pong", 10);

    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
        "ping", 10,
        std::bind(&Pong::subscribe_callback, this, std::placeholders::_1));
  }

private:
  void subscribe_callback(const std_msgs::msg::Int32::SharedPtr msg) {
    int32_t num = msg->data;
    RCLCPP_INFO(this->get_logger(), "Received: %d, Publishing %d", num,
                num + 1);

    delay_ = this->create_wall_timer(500ms, [this, num]() {
      if (num < 100)
        publish_message(num + 1);
      delay_->cancel();
    });
  }

  void publish_message(int32_t num) {
    auto message = std_msgs::msg::Int32();
    message.data = num;
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr delay_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Pong>());
  rclcpp::shutdown();
  return 0;
}
