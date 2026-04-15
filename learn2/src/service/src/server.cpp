#include <example_interfaces/srv/add_two_ints.hpp>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/utilities.hpp>

using Srv = example_interfaces::srv::AddTwoInts;

class Server : public rclcpp::Node {
public:
  Server() : Node("server") {
    srv_ = create_service<Srv>(
        "add_two_ints", std::bind(&Server::handle, this, std::placeholders::_1,
                                  std::placeholders::_2));
    RCLCPP_INFO(this->get_logger(), "Ready to add two ints.");
  }

private:
  void handle(const Srv::Request::SharedPtr req, Srv::Response::SharedPtr res) {
    res->sum = req->a + req->b;
    RCLCPP_INFO(this->get_logger(), "%ld + %ld = %ld", req->a, req->b,
                res->sum);
  }

  rclcpp::Service<Srv>::SharedPtr srv_;
};
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Server>());
  rclcpp::shutdown();
  return 0;
}
