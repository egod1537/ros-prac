// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:srv/Compute.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/srv/compute.h"


#ifndef MSGS__SRV__DETAIL__COMPUTE__STRUCT_H_
#define MSGS__SRV__DETAIL__COMPUTE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'operation'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Compute in the package msgs.
typedef struct msgs__srv__Compute_Request
{
  int32_t a;
  int32_t b;
  rosidl_runtime_c__String operation;
} msgs__srv__Compute_Request;

// Struct for a sequence of msgs__srv__Compute_Request.
typedef struct msgs__srv__Compute_Request__Sequence
{
  msgs__srv__Compute_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__Compute_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/Compute in the package msgs.
typedef struct msgs__srv__Compute_Response
{
  double result;
} msgs__srv__Compute_Response;

// Struct for a sequence of msgs__srv__Compute_Response.
typedef struct msgs__srv__Compute_Response__Sequence
{
  msgs__srv__Compute_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__Compute_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  msgs__srv__Compute_Event__request__MAX_SIZE = 1
};
// response
enum
{
  msgs__srv__Compute_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/Compute in the package msgs.
typedef struct msgs__srv__Compute_Event
{
  service_msgs__msg__ServiceEventInfo info;
  msgs__srv__Compute_Request__Sequence request;
  msgs__srv__Compute_Response__Sequence response;
} msgs__srv__Compute_Event;

// Struct for a sequence of msgs__srv__Compute_Event.
typedef struct msgs__srv__Compute_Event__Sequence
{
  msgs__srv__Compute_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__Compute_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__SRV__DETAIL__COMPUTE__STRUCT_H_
