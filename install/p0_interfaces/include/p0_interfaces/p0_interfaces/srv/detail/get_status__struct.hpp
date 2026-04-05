// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from p0_interfaces:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_HPP_
#define P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__p0_interfaces__srv__GetStatus_Request __attribute__((deprecated))
#else
# define DEPRECATED__p0_interfaces__srv__GetStatus_Request __declspec(deprecated)
#endif

namespace p0_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetStatus_Request_
{
  using Type = GetStatus_Request_<ContainerAllocator>;

  explicit GetStatus_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
    }
  }

  explicit GetStatus_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
    }
  }

  // field types and members
  using _robot_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_name_type robot_name;

  // setters for named parameter idiom
  Type & set__robot_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__p0_interfaces__srv__GetStatus_Request
    std::shared_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__p0_interfaces__srv__GetStatus_Request
    std::shared_ptr<p0_interfaces::srv::GetStatus_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetStatus_Request_ & other) const
  {
    if (this->robot_name != other.robot_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetStatus_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetStatus_Request_

// alias to use template instance with default allocator
using GetStatus_Request =
  p0_interfaces::srv::GetStatus_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace p0_interfaces


#ifndef _WIN32
# define DEPRECATED__p0_interfaces__srv__GetStatus_Response __attribute__((deprecated))
#else
# define DEPRECATED__p0_interfaces__srv__GetStatus_Response __declspec(deprecated)
#endif

namespace p0_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetStatus_Response_
{
  using Type = GetStatus_Response_<ContainerAllocator>;

  explicit GetStatus_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->battery = 0.0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->found = false;
    }
  }

  explicit GetStatus_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->battery = 0.0;
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      this->found = false;
    }
  }

  // field types and members
  using _battery_type =
    double;
  _battery_type battery;
  using _position_type =
    std::array<double, 3>;
  _position_type position;
  using _found_type =
    bool;
  _found_type found;

  // setters for named parameter idiom
  Type & set__battery(
    const double & _arg)
  {
    this->battery = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__found(
    const bool & _arg)
  {
    this->found = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__p0_interfaces__srv__GetStatus_Response
    std::shared_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__p0_interfaces__srv__GetStatus_Response
    std::shared_ptr<p0_interfaces::srv::GetStatus_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetStatus_Response_ & other) const
  {
    if (this->battery != other.battery) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->found != other.found) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetStatus_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetStatus_Response_

// alias to use template instance with default allocator
using GetStatus_Response =
  p0_interfaces::srv::GetStatus_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace p0_interfaces

namespace p0_interfaces
{

namespace srv
{

struct GetStatus
{
  using Request = p0_interfaces::srv::GetStatus_Request;
  using Response = p0_interfaces::srv::GetStatus_Response;
};

}  // namespace srv

}  // namespace p0_interfaces

#endif  // P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_HPP_
