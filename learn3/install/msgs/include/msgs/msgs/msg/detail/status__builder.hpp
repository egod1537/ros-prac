// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:msg/Status.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/msg/status.hpp"


#ifndef MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_
#define MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/msg/detail/status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace msg
{

namespace builder
{

class Init_Status_message
{
public:
  explicit Init_Status_message(::msgs::msg::Status & msg)
  : msg_(msg)
  {}
  ::msgs::msg::Status message(::msgs::msg::Status::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::Status msg_;
};

class Init_Status_level
{
public:
  explicit Init_Status_level(::msgs::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_message level(::msgs::msg::Status::_level_type arg)
  {
    msg_.level = std::move(arg);
    return Init_Status_message(msg_);
  }

private:
  ::msgs::msg::Status msg_;
};

class Init_Status_name
{
public:
  Init_Status_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Status_level name(::msgs::msg::Status::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Status_level(msg_);
  }

private:
  ::msgs::msg::Status msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::msg::Status>()
{
  return msgs::msg::builder::Init_Status_name();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_
