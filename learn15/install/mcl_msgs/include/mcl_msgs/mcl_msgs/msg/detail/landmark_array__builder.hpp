// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mcl_msgs:msg/LandmarkArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mcl_msgs/msg/landmark_array.hpp"


#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__BUILDER_HPP_
#define MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mcl_msgs/msg/detail/landmark_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mcl_msgs
{

namespace msg
{

namespace builder
{

class Init_LandmarkArray_landmarks
{
public:
  explicit Init_LandmarkArray_landmarks(::mcl_msgs::msg::LandmarkArray & msg)
  : msg_(msg)
  {}
  ::mcl_msgs::msg::LandmarkArray landmarks(::mcl_msgs::msg::LandmarkArray::_landmarks_type arg)
  {
    msg_.landmarks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mcl_msgs::msg::LandmarkArray msg_;
};

class Init_LandmarkArray_header
{
public:
  Init_LandmarkArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandmarkArray_landmarks header(::mcl_msgs::msg::LandmarkArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandmarkArray_landmarks(msg_);
  }

private:
  ::mcl_msgs::msg::LandmarkArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mcl_msgs::msg::LandmarkArray>()
{
  return mcl_msgs::msg::builder::Init_LandmarkArray_header();
}

}  // namespace mcl_msgs

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__BUILDER_HPP_
