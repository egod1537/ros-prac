// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from p0_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "p0_interfaces/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace p0_interfaces
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_is_active
{
public:
  explicit Init_RobotStatus_is_active(::p0_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::p0_interfaces::msg::RobotStatus is_active(::p0_interfaces::msg::RobotStatus::_is_active_type arg)
  {
    msg_.is_active = std::move(arg);
    return std::move(msg_);
  }

private:
  ::p0_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_position
{
public:
  explicit Init_RobotStatus_position(::p0_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_is_active position(::p0_interfaces::msg::RobotStatus::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_RobotStatus_is_active(msg_);
  }

private:
  ::p0_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_battery
{
public:
  explicit Init_RobotStatus_battery(::p0_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_position battery(::p0_interfaces::msg::RobotStatus::_battery_type arg)
  {
    msg_.battery = std::move(arg);
    return Init_RobotStatus_position(msg_);
  }

private:
  ::p0_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_name
{
public:
  Init_RobotStatus_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_battery name(::p0_interfaces::msg::RobotStatus::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_RobotStatus_battery(msg_);
  }

private:
  ::p0_interfaces::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::p0_interfaces::msg::RobotStatus>()
{
  return p0_interfaces::msg::builder::Init_RobotStatus_name();
}

}  // namespace p0_interfaces

#endif  // P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
