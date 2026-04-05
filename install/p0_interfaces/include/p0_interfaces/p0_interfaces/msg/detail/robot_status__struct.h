// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from p0_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
#define P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/RobotStatus in the package p0_interfaces.
typedef struct p0_interfaces__msg__RobotStatus
{
  rosidl_runtime_c__String name;
  double battery;
  double position[3];
  bool is_active;
} p0_interfaces__msg__RobotStatus;

// Struct for a sequence of p0_interfaces__msg__RobotStatus.
typedef struct p0_interfaces__msg__RobotStatus__Sequence
{
  p0_interfaces__msg__RobotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} p0_interfaces__msg__RobotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // P0_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
