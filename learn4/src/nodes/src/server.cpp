#include "msgs/action/countdown.hpp"
#include <memory>
#include <msgs/action/countdown.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>
#include <rclcpp_action/create_server.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <rclcpp_action/server.hpp>
#include <rclcpp_action/server_goal_handle.hpp>
#include <rclcpp_action/types.hpp>
#include <thread>

using Countdown = msgs::action::Countdown;
using GoalHandle = rclcpp_action::ServerGoalHandle<Countdown>;

class CountdownServer : public rclcpp::Node {
public:
  CountdownServer() : Node("countdown_server") {
    server_ = rclcpp_action::create_server<Countdown>(
        this, "countdown",
        std::bind(&CountdownServer::handle_goal, this, std::placeholders::_1,
                  std::placeholders::_2),
        std::bind(&CountdownServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&CountdownServer::handle_accepted, this,
                  std::placeholders::_1));
    RCLCPP_INFO(get_logger(), "Countdown server ready.");
  }

private:
  rclcpp_action::GoalResponse
  handle_goal(const rclcpp_action::GoalUUID &,
              std::shared_ptr<const Countdown::Goal> goal) {
    RCLCPP_INFO(get_logger(), "Goal received: %d seconds",
                goal->target_seconds);
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse
  handle_cancel(const std::shared_ptr<GoalHandle>) {
    RCLCPP_INFO(this->get_logger(), "Cancel requested");
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle) {
    std::thread([this, goal_handle] { execute(goal_handle); }).detach();
  }

  void execute(const std::shared_ptr<GoalHandle> goal_handle) {
    auto feedback = std::make_shared<Countdown::Feedback>();
    auto result = std::make_shared<Countdown::Result>();
    int remaining = goal_handle->get_goal()->target_seconds;

    rclcpp::Rate rate(1.0);
    while (remaining > 0 && rclcpp::ok()) {
      if (goal_handle->is_canceling()) {
        result->message = "Cancelled at " + std::to_string(remaining);
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Cancelled");
        return;
      }

      feedback->remaining = remaining;
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(), "Remaining: %d", remaining);
      remaining--;
      rate.sleep();
    }

    result->message = "Countdown complete!";
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "Done !");
  }

  rclcpp_action::Server<Countdown>::SharedPtr server_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CountdownServer>());
  rclcpp::shutdown();
  return 0;
}
