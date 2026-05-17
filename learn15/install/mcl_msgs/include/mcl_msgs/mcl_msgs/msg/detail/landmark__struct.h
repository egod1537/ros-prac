// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mcl_msgs/msg/landmark.h"


#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_H_
#define MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Landmark in the package mcl_msgs.
typedef struct mcl_msgs__msg__Landmark
{
  int32_t id;
  double range;
  double bearing;
} mcl_msgs__msg__Landmark;

// Struct for a sequence of mcl_msgs__msg__Landmark.
typedef struct mcl_msgs__msg__Landmark__Sequence
{
  mcl_msgs__msg__Landmark * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mcl_msgs__msg__Landmark__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK__STRUCT_H_
