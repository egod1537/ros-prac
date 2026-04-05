// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from p0_interfaces:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_H_
#define P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetStatus in the package p0_interfaces.
typedef struct p0_interfaces__srv__GetStatus_Request
{
  rosidl_runtime_c__String robot_name;
} p0_interfaces__srv__GetStatus_Request;

// Struct for a sequence of p0_interfaces__srv__GetStatus_Request.
typedef struct p0_interfaces__srv__GetStatus_Request__Sequence
{
  p0_interfaces__srv__GetStatus_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} p0_interfaces__srv__GetStatus_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GetStatus in the package p0_interfaces.
typedef struct p0_interfaces__srv__GetStatus_Response
{
  double battery;
  double position[3];
  bool found;
} p0_interfaces__srv__GetStatus_Response;

// Struct for a sequence of p0_interfaces__srv__GetStatus_Response.
typedef struct p0_interfaces__srv__GetStatus_Response__Sequence
{
  p0_interfaces__srv__GetStatus_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} p0_interfaces__srv__GetStatus_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // P0_INTERFACES__SRV__DETAIL__GET_STATUS__STRUCT_H_
