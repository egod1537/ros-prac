#include "rcl_interfaces/msg/integer_range.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include <chrono>
#include <memory>
#include <random>
#include <rclcpp/create_timer.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node_interfaces/node_parameters_interface.hpp>
#include <rclcpp/parameter.hpp>
#include <rclcpp/parameter_service.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

class Heater : public rclcpp::Node {
public:
  Heater() : Node("heater") {
    declare_parameter("target_temp", 22.0);
    declare_parameter("mode", "auto");

    rcl_interfaces::msg::ParameterDescriptor power_desc;
    power_desc.description = "heater power 0-100";

    rcl_interfaces::msg::IntegerRange range;
    range.from_value = 0;
    range.to_value = 100;
    range.step = 1;
    power_desc.integer_range.push_back(range);
    declare_parameter("power", 50, power_desc);

    cb_handle_ = add_on_set_parameters_callback(
        [this](const std::vector<rclcpp::Parameter> &params) {
          return on_param_change(params);
        });

    print_state();

    timer_ =
        create_wall_timer(std::chrono::seconds(3), [this]() { print_state(); });
  }

private:
  rcl_interfaces::msg::SetParametersResult
  on_param_change(const std::vector<rclcpp::Parameter> &params) {
    rcl_interfaces::msg::SetParametersResult result;
    result.successful = true;

    for (const auto &p : params) {
      if (p.get_name() == "mode") {
        auto v = p.as_string();
        if (v != "auto" && v != "heat" && v != "cool") {
          result.successful = false;
          result.reason = "mode must be auto|heat|cool, got: " + v;
          RCLCPP_INFO(this->get_logger(), "%s", result.reason.c_str());
          return result;
        }
      }

      RCLCPP_INFO(this->get_logger(), p.get_name().c_str(),
                  p.value_to_string().c_str());
    }

    return result;
  }

  void print_state() {
    double temp = get_parameter("target_temp").as_double();
    int power = get_parameter("power").as_int();
    std::string mode = get_parameter("mode").as_string();

    RCLCPP_INFO(this->get_logger(), "[state] target=%.1f, power=%d mode=%s",
                temp, power, mode.c_str());
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr cb_handle_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Heater>());
  rclcpp::shutdown();
  return 0;
}
