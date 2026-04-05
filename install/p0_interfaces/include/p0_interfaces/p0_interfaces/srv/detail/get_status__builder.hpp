// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from p0_interfaces:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__SRV__DETAIL__GET_STATUS__BUILDER_HPP_
#define P0_INTERFACES__SRV__DETAIL__GET_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "p0_interfaces/srv/detail/get_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace p0_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetStatus_Request_robot_name
{
public:
  Init_GetStatus_Request_robot_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::p0_interfaces::srv::GetStatus_Request robot_name(::p0_interfaces::srv::GetStatus_Request::_robot_name_type arg)
  {
    msg_.robot_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::p0_interfaces::srv::GetStatus_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::p0_interfaces::srv::GetStatus_Request>()
{
  return p0_interfaces::srv::builder::Init_GetStatus_Request_robot_name();
}

}  // namespace p0_interfaces


namespace p0_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetStatus_Response_found
{
public:
  explicit Init_GetStatus_Response_found(::p0_interfaces::srv::GetStatus_Response & msg)
  : msg_(msg)
  {}
  ::p0_interfaces::srv::GetStatus_Response found(::p0_interfaces::srv::GetStatus_Response::_found_type arg)
  {
    msg_.found = std::move(arg);
    return std::move(msg_);
  }

private:
  ::p0_interfaces::srv::GetStatus_Response msg_;
};

class Init_GetStatus_Response_position
{
public:
  explicit Init_GetStatus_Response_position(::p0_interfaces::srv::GetStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetStatus_Response_found position(::p0_interfaces::srv::GetStatus_Response::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_GetStatus_Response_found(msg_);
  }

private:
  ::p0_interfaces::srv::GetStatus_Response msg_;
};

class Init_GetStatus_Response_battery
{
public:
  Init_GetStatus_Response_battery()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetStatus_Response_position battery(::p0_interfaces::srv::GetStatus_Response::_battery_type arg)
  {
    msg_.battery = std::move(arg);
    return Init_GetStatus_Response_position(msg_);
  }

private:
  ::p0_interfaces::srv::GetStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::p0_interfaces::srv::GetStatus_Response>()
{
  return p0_interfaces::srv::builder::Init_GetStatus_Response_battery();
}

}  // namespace p0_interfaces

#endif  // P0_INTERFACES__SRV__DETAIL__GET_STATUS__BUILDER_HPP_
