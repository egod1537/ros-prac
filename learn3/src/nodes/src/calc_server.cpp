#include "msgs/msg/status.hpp"
#include "msgs/srv/compute.hpp"
#include <memory>
#include <msgs/srv/compute.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/utilities.hpp>

using MsgCompute = msgs::srv::Compute;

class CalcServer : public rclcpp::Node {
public:
  CalcServer() : Node("calc_server") {
    srv_ = create_service<MsgCompute>(
        "compute", std::bind(&CalcServer::handle, this, std::placeholders::_1,
                             std::placeholders::_2));
  }

private:
  void handle(const MsgCompute::Request::SharedPtr req,
              MsgCompute::Response::SharedPtr res) {
    if (req->operation == "add")
      res->result = req->a + req->b;
    else if (req->operation == "sub")
      res->result = req->a - req->b;
    else if (req->operation == "mul")
      res->result = req->a * req->b;
    else if (req->operation == "div")
      res->result = req->b != 0 ? (double)req->a / req->b : 0.0;
    else
      res->result = 0.0;

    RCLCPP_INFO(get_logger(), "%d %s %d = %.2f", req->a, req->operation.c_str(),
                req->b, res->result);
  }

  rclcpp::Service<MsgCompute>::SharedPtr srv_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CalcServer>());
  rclcpp::shutdown();
  return 0;
}
