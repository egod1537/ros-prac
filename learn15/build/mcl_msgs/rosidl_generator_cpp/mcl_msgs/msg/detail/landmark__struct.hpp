// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mcl_msgs/msg/landmark.hpp"


#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_HPP_
#define MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__mcl_msgs__msg__Landmark __attribute__((deprecated))
#else
# define DEPRECATED__mcl_msgs__msg__Landmark __declspec(deprecated)
#endif

namespace mcl_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Landmark_
{
  using Type = Landmark_<ContainerAllocator>;

  explicit Landmark_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->range = 0.0;
      this->bearing = 0.0;
    }
  }

  explicit Landmark_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->range = 0.0;
      this->bearing = 0.0;
    }
  }

  // field types and members
  using _id_type =
    int32_t;
  _id_type id;
  using _range_type =
    double;
  _range_type range;
  using _bearing_type =
    double;
  _bearing_type bearing;

  // setters for named parameter idiom
  Type & set__id(
    const int32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__range(
    const double & _arg)
  {
    this->range = _arg;
    return *this;
  }
  Type & set__bearing(
    const double & _arg)
  {
    this->bearing = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mcl_msgs::msg::Landmark_<ContainerAllocator> *;
  using ConstRawPtr =
    const mcl_msgs::msg::Landmark_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mcl_msgs::msg::Landmark_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mcl_msgs::msg::Landmark_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mcl_msgs__msg__Landmark
    std::shared_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mcl_msgs__msg__Landmark
    std::shared_ptr<mcl_msgs::msg::Landmark_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Landmark_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->range != other.range) {
      return false;
    }
    if (this->bearing != other.bearing) {
      return false;
    }
    return true;
  }
  bool operator!=(const Landmark_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Landmark_

// alias to use template instance with default allocator
using Landmark =
  mcl_msgs::msg::Landmark_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mcl_msgs

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_HPP_
