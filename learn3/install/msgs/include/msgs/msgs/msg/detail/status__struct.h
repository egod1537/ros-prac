// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:msg/Status.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/msg/status.h"


#ifndef MSGS__MSG__DETAIL__STATUS__STRUCT_H_
#define MSGS__MSG__DETAIL__STATUS__STRUCT_H_

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
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Status in the package msgs.
typedef struct msgs__msg__Status
{
  rosidl_runtime_c__String name;
  int32_t level;
  rosidl_runtime_c__String message;
} msgs__msg__Status;

// Struct for a sequence of msgs__msg__Status.
typedef struct msgs__msg__Status__Sequence
{
  msgs__msg__Status * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__msg__Status__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__MSG__DETAIL__STATUS__STRUCT_H_
