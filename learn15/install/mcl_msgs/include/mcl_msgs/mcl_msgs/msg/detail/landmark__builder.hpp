// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mcl_msgs/msg/landmark.hpp"


#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK__BUILDER_HPP_
#define MCL_MSGS__MSG__DETAIL__LANDMARK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mcl_msgs/msg/detail/landmark__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mcl_msgs
{

namespace msg
{

namespace builder
{

class Init_Landmark_bearing
{
public:
  explicit Init_Landmark_bearing(::mcl_msgs::msg::Landmark & msg)
  : msg_(msg)
  {}
  ::mcl_msgs::msg::Landmark bearing(::mcl_msgs::msg::Landmark::_bearing_type arg)
  {
    msg_.bearing = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mcl_msgs::msg::Landmark msg_;
};

class Init_Landmark_range
{
public:
  explicit Init_Landmark_range(::mcl_msgs::msg::Landmark & msg)
  : msg_(msg)
  {}
  Init_Landmark_bearing range(::mcl_msgs::msg::Landmark::_range_type arg)
  {
    msg_.range = std::move(arg);
    return Init_Landmark_bearing(msg_);
  }

private:
  ::mcl_msgs::msg::Landmark msg_;
};

class Init_Landmark_id
{
public:
  Init_Landmark_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Landmark_range id(::mcl_msgs::msg::Landmark::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Landmark_range(msg_);
  }

private:
  ::mcl_msgs::msg::Landmark msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mcl_msgs::msg::Landmark>()
{
  return mcl_msgs::msg::builder::Init_Landmark_id();
}

}  // namespace mcl_msgs

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK__BUILDER_HPP_
