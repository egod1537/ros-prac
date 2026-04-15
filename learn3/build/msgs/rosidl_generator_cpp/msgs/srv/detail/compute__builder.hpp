// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:srv/Compute.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/srv/compute.hpp"


#ifndef MSGS__SRV__DETAIL__COMPUTE__BUILDER_HPP_
#define MSGS__SRV__DETAIL__COMPUTE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/srv/detail/compute__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace srv
{

namespace builder
{

class Init_Compute_Request_operation
{
public:
  explicit Init_Compute_Request_operation(::msgs::srv::Compute_Request & msg)
  : msg_(msg)
  {}
  ::msgs::srv::Compute_Request operation(::msgs::srv::Compute_Request::_operation_type arg)
  {
    msg_.operation = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::srv::Compute_Request msg_;
};

class Init_Compute_Request_b
{
public:
  explicit Init_Compute_Request_b(::msgs::srv::Compute_Request & msg)
  : msg_(msg)
  {}
  Init_Compute_Request_operation b(::msgs::srv::Compute_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_Compute_Request_operation(msg_);
  }

private:
  ::msgs::srv::Compute_Request msg_;
};

class Init_Compute_Request_a
{
public:
  Init_Compute_Request_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Compute_Request_b a(::msgs::srv::Compute_Request::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Compute_Request_b(msg_);
  }

private:
  ::msgs::srv::Compute_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::Compute_Request>()
{
  return msgs::srv::builder::Init_Compute_Request_a();
}

}  // namespace msgs


namespace msgs
{

namespace srv
{

namespace builder
{

class Init_Compute_Response_result
{
public:
  Init_Compute_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::srv::Compute_Response result(::msgs::srv::Compute_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::srv::Compute_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::Compute_Response>()
{
  return msgs::srv::builder::Init_Compute_Response_result();
}

}  // namespace msgs


namespace msgs
{

namespace srv
{

namespace builder
{

class Init_Compute_Event_response
{
public:
  explicit Init_Compute_Event_response(::msgs::srv::Compute_Event & msg)
  : msg_(msg)
  {}
  ::msgs::srv::Compute_Event response(::msgs::srv::Compute_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::srv::Compute_Event msg_;
};

class Init_Compute_Event_request
{
public:
  explicit Init_Compute_Event_request(::msgs::srv::Compute_Event & msg)
  : msg_(msg)
  {}
  Init_Compute_Event_response request(::msgs::srv::Compute_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Compute_Event_response(msg_);
  }

private:
  ::msgs::srv::Compute_Event msg_;
};

class Init_Compute_Event_info
{
public:
  Init_Compute_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Compute_Event_request info(::msgs::srv::Compute_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Compute_Event_request(msg_);
  }

private:
  ::msgs::srv::Compute_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::srv::Compute_Event>()
{
  return msgs::srv::builder::Init_Compute_Event_info();
}

}  // namespace msgs

#endif  // MSGS__SRV__DETAIL__COMPUTE__BUILDER_HPP_
