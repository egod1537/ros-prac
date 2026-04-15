#include "example_interfaces/srv/add_two_ints.hpp"
#include <chrono>
#include <example_interfaces/srv/add_two_ints.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/future_return_code.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>

using Srv = example_interfaces::srv::AddTwoInts;

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("client");
  auto client = node->create_client<Srv>("add_two_ints");

  while (!client->wait_for_service(std::chrono::seconds(1))) {
    RCLCPP_INFO(node->get_logger(), "Waiting for server...");
  }

  auto req = std::make_shared<Srv::Request>();
  req->a = 10;
  req->b = 25;

  auto future = client->async_send_request(req);
  if (rclcpp::spin_until_future_complete(node, future) ==
      rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(node->get_logger(), "Result: '%ld", future.get()->sum);
  } else {
    RCLCPP_INFO(node->get_logger(), "Failed to call service");
  }

  rclcpp::shutdown();
  return 0;
}
