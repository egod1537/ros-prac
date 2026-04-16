// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:srv/GetAverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/srv/get_average.h"


#ifndef MSGS__SRV__DETAIL__GET_AVERAGE__STRUCT_H_
#define MSGS__SRV__DETAIL__GET_AVERAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetAverage in the package msgs.
typedef struct msgs__srv__GetAverage_Request
{
  uint8_t structure_needs_at_least_one_member;
} msgs__srv__GetAverage_Request;

// Struct for a sequence of msgs__srv__GetAverage_Request.
typedef struct msgs__srv__GetAverage_Request__Sequence
{
  msgs__srv__GetAverage_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__GetAverage_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/GetAverage in the package msgs.
typedef struct msgs__srv__GetAverage_Response
{
  double temperature;
} msgs__srv__GetAverage_Response;

// Struct for a sequence of msgs__srv__GetAverage_Response.
typedef struct msgs__srv__GetAverage_Response__Sequence
{
  msgs__srv__GetAverage_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__GetAverage_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  msgs__srv__GetAverage_Event__request__MAX_SIZE = 1
};
// response
enum
{
  msgs__srv__GetAverage_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetAverage in the package msgs.
typedef struct msgs__srv__GetAverage_Event
{
  service_msgs__msg__ServiceEventInfo info;
  msgs__srv__GetAverage_Request__Sequence request;
  msgs__srv__GetAverage_Response__Sequence response;
} msgs__srv__GetAverage_Event;

// Struct for a sequence of msgs__srv__GetAverage_Event.
typedef struct msgs__srv__GetAverage_Event__Sequence
{
  msgs__srv__GetAverage_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__srv__GetAverage_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__SRV__DETAIL__GET_AVERAGE__STRUCT_H_
