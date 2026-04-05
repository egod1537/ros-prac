#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <p0_interfaces/msg/detail/robot_status__struct.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

#include "p0_interfaces/msg/robot_status.hpp"

using namespace std::chrono_literals;
using RobotStatusMsg = p0_interfaces::msg::RobotStatus;

class StatusPublisher : public rclcpp::Node {
public:
  StatusPublisher() : Node("status_publisher") {
    publisher_ = this->create_publisher<RobotStatusMsg>("topic", 10);

    timer_ = this->create_wall_timer(
        1000ms, std::bind(&StatusPublisher::publish_status, this));
  }

private:
  void publish_status() {
    auto message = RobotStatusMsg();
    message.battery = 100;
    message.name = "yang";
    message.position = {1.0f, 2.0f, 3.0f};
    message.is_active = true;
    RCLCPP_INFO(this->get_logger(),
                "Publishing name='%s' battery='%f' position=('%f', '%f', "
                "'%f'), is_active=%d",
                message.name.c_str(), message.battery,
                std::get<0>(message.position), std::get<1>(message.position),
                std::get<2>(message.position), message.is_active);
    publisher_->publish(message);
  }

  rclcpp::Publisher<RobotStatusMsg>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StatusPublisher>());
  rclcpp::shutdown();
  return 0;
}
