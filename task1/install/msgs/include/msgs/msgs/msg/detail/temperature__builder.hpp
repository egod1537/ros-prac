// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:msg/Temperature.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/msg/temperature.hpp"


#ifndef MSGS__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_
#define MSGS__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/msg/detail/temperature__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace msg
{

namespace builder
{

class Init_Temperature_time
{
public:
  explicit Init_Temperature_time(::msgs::msg::Temperature & msg)
  : msg_(msg)
  {}
  ::msgs::msg::Temperature time(::msgs::msg::Temperature::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::Temperature msg_;
};

class Init_Temperature_temperature
{
public:
  explicit Init_Temperature_temperature(::msgs::msg::Temperature & msg)
  : msg_(msg)
  {}
  Init_Temperature_time temperature(::msgs::msg::Temperature::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Temperature_time(msg_);
  }

private:
  ::msgs::msg::Temperature msg_;
};

class Init_Temperature_name
{
public:
  Init_Temperature_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Temperature_temperature name(::msgs::msg::Temperature::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Temperature_temperature(msg_);
  }

private:
  ::msgs::msg::Temperature msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::msg::Temperature>()
{
  return msgs::msg::builder::Init_Temperature_name();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_
