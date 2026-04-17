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

class Init_Temperature_unit
{
public:
  explicit Init_Temperature_unit(::msgs::msg::Temperature & msg)
  : msg_(msg)
  {}
  ::msgs::msg::Temperature unit(::msgs::msg::Temperature::_unit_type arg)
  {
    msg_.unit = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::Temperature msg_;
};

class Init_Temperature_value
{
public:
  Init_Temperature_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Temperature_unit value(::msgs::msg::Temperature::_value_type arg)
  {
    msg_.value = std::move(arg);
    return Init_Temperature_unit(msg_);
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
  return msgs::msg::builder::Init_Temperature_value();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_
