// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msgs:msg/Temperature.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/msg/temperature.hpp"


#ifndef MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_HPP_
#define MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__msgs__msg__Temperature __attribute__((deprecated))
#else
# define DEPRECATED__msgs__msg__Temperature __declspec(deprecated)
#endif

namespace msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Temperature_
{
  using Type = Temperature_<ContainerAllocator>;

  explicit Temperature_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->temperature = 0.0;
      this->time = 0l;
    }
  }

  explicit Temperature_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->temperature = 0.0;
      this->time = 0l;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _temperature_type =
    double;
  _temperature_type temperature;
  using _time_type =
    int32_t;
  _time_type time;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__temperature(
    const double & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__time(
    const int32_t & _arg)
  {
    this->time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msgs::msg::Temperature_<ContainerAllocator> *;
  using ConstRawPtr =
    const msgs::msg::Temperature_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msgs::msg::Temperature_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msgs::msg::Temperature_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Temperature_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Temperature_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Temperature_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Temperature_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msgs::msg::Temperature_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msgs::msg::Temperature_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msgs__msg__Temperature
    std::shared_ptr<msgs::msg::Temperature_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msgs__msg__Temperature
    std::shared_ptr<msgs::msg::Temperature_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Temperature_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->time != other.time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Temperature_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Temperature_

// alias to use template instance with default allocator
using Temperature =
  msgs::msg::Temperature_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_HPP_
