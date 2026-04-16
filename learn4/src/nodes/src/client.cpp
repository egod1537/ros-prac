#include "msgs/action/countdown.hpp"
#include <chrono>
#include <memory>
#include <msgs/action/countdown.hpp>
#include <rclcpp/client.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>
#include <rclcpp_action/client.hpp>
#include <rclcpp_action/create_client.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

using Countdown = msgs::action::Countdown;
using GoalHandle = rclcpp_action::ClientGoalHandle<Countdown>;

class CountdownClient : public rclcpp::Node {
public:
  CountdownClient() : Node("countdown_client") {
    client_ = rclcpp_action::create_client<Countdown>(this, "countdown");
  }

  void send_goal(int seconds) {
    if (!client_->wait_for_action_server(std::chrono::seconds(5))) {
      RCLCPP_INFO(this->get_logger(), "Server not available");
      return;
    }

    auto goal = Countdown::Goal();
    goal.target_seconds = seconds;

    auto opts = rclcpp_action::Client<Countdown>::SendGoalOptions();

    opts.goal_response_callback =
        [this](const GoalHandle::SharedPtr &goal_handle) {
          if (!goal_handle) {
            RCLCPP_ERROR(this->get_logger(), "Goal rejected");
          } else {
            RCLCPP_INFO(this->get_logger(), "Goal accepted");
          }
        };

    opts.feedback_callback =
        [this](GoalHandle::SharedPtr,
               const std::shared_ptr<const Countdown::Feedback> feedback) {
          RCLCPP_INFO(this->get_logger(), "Remaining %d", feedback->remaining);
        };

    opts.result_callback = [this](const GoalHandle::WrappedResult &result) {
      switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        RCLCPP_INFO(get_logger(), "Result: %s", result.result->message.c_str());
        break;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_WARN(get_logger(), "Canceled: %s",
                    result.result->message.c_str());
        break;
      default:
        RCLCPP_ERROR(get_logger(), "Failed");
        break;
      }
      rclcpp::shutdown();
    };

    client_->async_send_goal(goal, opts);
  }

private:
  rclcpp_action::Client<Countdown>::SharedPtr client_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CountdownClient>();
  node->send_goal(5);
  rclcpp::spin(node);
  return 0;
}
