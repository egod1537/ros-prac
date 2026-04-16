// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:srv/GetAverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/srv/get_average.hpp"


#ifndef MSGS__SRV__DETAIL__GET_AVERAGE__BUILDER_HPP_
#define MSGS__SRV__DETAIL__GET_AVERAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/srv/detail/get_average__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::GetAverage_Request>()
{
  return ::msgs::srv::GetAverage_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace msgs


namespace msgs
{

namespace srv
{

namespace builder
{

class Init_GetAverage_Response_temperature
{
public:
  Init_GetAverage_Response_temperature()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::srv::GetAverage_Response temperature(::msgs::srv::GetAverage_Response::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::srv::GetAverage_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::GetAverage_Response>()
{
  return msgs::srv::builder::Init_GetAverage_Response_temperature();
}

}  // namespace msgs


namespace msgs
{

namespace srv
{

namespace builder
{

class Init_GetAverage_Event_response
{
public:
  explicit Init_GetAverage_Event_response(::msgs::srv::GetAverage_Event & msg)
  : msg_(msg)
  {}
  ::msgs::srv::GetAverage_Event response(::msgs::srv::GetAverage_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::srv::GetAverage_Event msg_;
};

class Init_GetAverage_Event_request
{
public:
  explicit Init_GetAverage_Event_request(::msgs::srv::GetAverage_Event & msg)
  : msg_(msg)
  {}
  Init_GetAverage_Event_response request(::msgs::srv::GetAverage_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetAverage_Event_response(msg_);
  }

private:
  ::msgs::srv::GetAverage_Event msg_;
};

class Init_GetAverage_Event_info
{
public:
  Init_GetAverage_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAverage_Event_request info(::msgs::srv::GetAverage_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetAverage_Event_request(msg_);
  }

private:
  ::msgs::srv::GetAverage_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::GetAverage_Event>()
{
  return msgs::srv::builder::Init_GetAverage_Event_info();
}

}  // namespace msgs

#endif  // MSGS__SRV__DETAIL__GET_AVERAGE__BUILDER_HPP_
