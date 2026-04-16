#include "msgs/msg/temperature.hpp"
#include "msgs/srv/get_average.hpp"
#include <functional>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/utilities.hpp>

using SrvAverage = msgs::srv::GetAverage;
using MsgTemperature = msgs::msg::Temperature;

class Monitor : public rclcpp::Node {
public:
  Monitor() : Node("monitor"), sum_(0.0), count_(0) {
    sub_ = create_subscription<MsgTemperature>(
        "temperature", 10,
        std::bind(&Monitor::receive, this, std::placeholders::_1));
    srv_ = create_service<SrvAverage>(
        "get_average", std::bind(&Monitor::handle, this, std::placeholders::_1,
                                 std::placeholders::_2));
  }

private:
  void handle(const SrvAverage::Request::SharedPtr req,
              SrvAverage::Response::SharedPtr res) {
    res->temperature = count_ == 0 ? 0 : sum_ / count_;
    RCLCPP_INFO(this->get_logger(), "Average Temperature : %.2f",
                res->temperature);
  }

  void receive(const MsgTemperature::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "[%s] %.2f°C (t=%d)", msg->name.c_str(),
                msg->temperature, msg->time);
    count_++;
    sum_ += msg->temperature;
  }

  rclcpp::Subscription<MsgTemperature>::SharedPtr sub_;
  rclcpp::Service<SrvAverage>::SharedPtr srv_;
  double sum_;
  int count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Monitor>());
  rclcpp::shutdown();
  return 0;
}
