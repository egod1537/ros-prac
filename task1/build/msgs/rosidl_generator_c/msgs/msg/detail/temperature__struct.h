// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:msg/Temperature.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/msg/temperature.h"


#ifndef MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_H_
#define MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_H_

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

/// Struct defined in msg/Temperature in the package msgs.
typedef struct msgs__msg__Temperature
{
  rosidl_runtime_c__String name;
  double temperature;
  int32_t time;
} msgs__msg__Temperature;

// Struct for a sequence of msgs__msg__Temperature.
typedef struct msgs__msg__Temperature__Sequence
{
  msgs__msg__Temperature * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__msg__Temperature__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__MSG__DETAIL__TEMPERATURE__STRUCT_H_
