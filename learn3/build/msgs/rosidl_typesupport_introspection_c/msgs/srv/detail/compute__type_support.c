// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from msgs:srv/Compute.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "msgs/srv/detail/compute__rosidl_typesupport_introspection_c.h"
#include "msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "msgs/srv/detail/compute__functions.h"
#include "msgs/srv/detail/compute__struct.h"


// Include directives for member types
// Member `operation`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msgs__srv__Compute_Request__init(message_memory);
}

void msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_fini_function(void * message_memory)
{
  msgs__srv__Compute_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_member_array[3] = {
  {
    "a",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__srv__Compute_Request, a),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "b",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__srv__Compute_Request, b),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "operation",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__srv__Compute_Request, operation),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_members = {
  "msgs__srv",  // message namespace
  "Compute_Request",  // message name
  3,  // number of fields
  sizeof(msgs__srv__Compute_Request),
  false,  // has_any_key_member_
  msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_member_array,  // message members
  msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle = {
  0,
  &msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_members,
  get_message_typesupport_handle_function,
  &msgs__srv__Compute_Request__get_type_hash,
  &msgs__srv__Compute_Request__get_type_description,
  &msgs__srv__Compute_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Request)() {
  if (!msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle.typesupport_identifier) {
    msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "msgs/srv/detail/compute__rosidl_typesupport_introspection_c.h"
// already included above
// #include "msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "msgs/srv/detail/compute__functions.h"
// already included above
// #include "msgs/srv/detail/compute__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msgs__srv__Compute_Response__init(message_memory);
}

void msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_fini_function(void * message_memory)
{
  msgs__srv__Compute_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__srv__Compute_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_members = {
  "msgs__srv",  // message namespace
  "Compute_Response",  // message name
  1,  // number of fields
  sizeof(msgs__srv__Compute_Response),
  false,  // has_any_key_member_
  msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_member_array,  // message members
  msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle = {
  0,
  &msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_members,
  get_message_typesupport_handle_function,
  &msgs__srv__Compute_Response__get_type_hash,
  &msgs__srv__Compute_Response__get_type_description,
  &msgs__srv__Compute_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Response)() {
  if (!msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle.typesupport_identifier) {
    msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "msgs/srv/detail/compute__rosidl_typesupport_introspection_c.h"
// already included above
// #include "msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "msgs/srv/detail/compute__functions.h"
// already included above
// #include "msgs/srv/detail/compute__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "msgs/srv/compute.h"
// Member `request`
// Member `response`
// already included above
// #include "msgs/srv/detail/compute__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msgs__srv__Compute_Event__init(message_memory);
}

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_fini_function(void * message_memory)
{
  msgs__srv__Compute_Event__fini(message_memory);
}

size_t msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__size_function__Compute_Event__request(
  const void * untyped_member)
{
  const msgs__srv__Compute_Request__Sequence * member =
    (const msgs__srv__Compute_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__request(
  const void * untyped_member, size_t index)
{
  const msgs__srv__Compute_Request__Sequence * member =
    (const msgs__srv__Compute_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__request(
  void * untyped_member, size_t index)
{
  msgs__srv__Compute_Request__Sequence * member =
    (msgs__srv__Compute_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__fetch_function__Compute_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const msgs__srv__Compute_Request * item =
    ((const msgs__srv__Compute_Request *)
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__request(untyped_member, index));
  msgs__srv__Compute_Request * value =
    (msgs__srv__Compute_Request *)(untyped_value);
  *value = *item;
}

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__assign_function__Compute_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  msgs__srv__Compute_Request * item =
    ((msgs__srv__Compute_Request *)
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__request(untyped_member, index));
  const msgs__srv__Compute_Request * value =
    (const msgs__srv__Compute_Request *)(untyped_value);
  *item = *value;
}

bool msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__resize_function__Compute_Event__request(
  void * untyped_member, size_t size)
{
  msgs__srv__Compute_Request__Sequence * member =
    (msgs__srv__Compute_Request__Sequence *)(untyped_member);
  msgs__srv__Compute_Request__Sequence__fini(member);
  return msgs__srv__Compute_Request__Sequence__init(member, size);
}

size_t msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__size_function__Compute_Event__response(
  const void * untyped_member)
{
  const msgs__srv__Compute_Response__Sequence * member =
    (const msgs__srv__Compute_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__response(
  const void * untyped_member, size_t index)
{
  const msgs__srv__Compute_Response__Sequence * member =
    (const msgs__srv__Compute_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__response(
  void * untyped_member, size_t index)
{
  msgs__srv__Compute_Response__Sequence * member =
    (msgs__srv__Compute_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__fetch_function__Compute_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const msgs__srv__Compute_Response * item =
    ((const msgs__srv__Compute_Response *)
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__response(untyped_member, index));
  msgs__srv__Compute_Response * value =
    (msgs__srv__Compute_Response *)(untyped_value);
  *value = *item;
}

void msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__assign_function__Compute_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  msgs__srv__Compute_Response * item =
    ((msgs__srv__Compute_Response *)
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__response(untyped_member, index));
  const msgs__srv__Compute_Response * value =
    (const msgs__srv__Compute_Response *)(untyped_value);
  *item = *value;
}

bool msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__resize_function__Compute_Event__response(
  void * untyped_member, size_t size)
{
  msgs__srv__Compute_Response__Sequence * member =
    (msgs__srv__Compute_Response__Sequence *)(untyped_member);
  msgs__srv__Compute_Response__Sequence__fini(member);
  return msgs__srv__Compute_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__srv__Compute_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(msgs__srv__Compute_Event, request),  // bytes offset in struct
    NULL,  // default value
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__size_function__Compute_Event__request,  // size() function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__request,  // get_const(index) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__request,  // get(index) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__fetch_function__Compute_Event__request,  // fetch(index, &value) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__assign_function__Compute_Event__request,  // assign(index, value) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__resize_function__Compute_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(msgs__srv__Compute_Event, response),  // bytes offset in struct
    NULL,  // default value
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__size_function__Compute_Event__response,  // size() function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_const_function__Compute_Event__response,  // get_const(index) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__get_function__Compute_Event__response,  // get(index) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__fetch_function__Compute_Event__response,  // fetch(index, &value) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__assign_function__Compute_Event__response,  // assign(index, value) function pointer
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__resize_function__Compute_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_members = {
  "msgs__srv",  // message namespace
  "Compute_Event",  // message name
  3,  // number of fields
  sizeof(msgs__srv__Compute_Event),
  false,  // has_any_key_member_
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_member_array,  // message members
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_type_support_handle = {
  0,
  &msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_members,
  get_message_typesupport_handle_function,
  &msgs__srv__Compute_Event__get_type_hash,
  &msgs__srv__Compute_Event__get_type_description,
  &msgs__srv__Compute_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Event)() {
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Request)();
  msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Response)();
  if (!msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_type_support_handle.typesupport_identifier) {
    msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "msgs/srv/detail/compute__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_members = {
  "msgs__srv",  // service namespace
  "Compute",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle,
  NULL,  // response message
  // msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle
  NULL  // event_message
  // msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle
};


static rosidl_service_type_support_t msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_type_support_handle = {
  0,
  &msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_members,
  get_service_typesupport_handle_function,
  &msgs__srv__Compute_Request__rosidl_typesupport_introspection_c__Compute_Request_message_type_support_handle,
  &msgs__srv__Compute_Response__rosidl_typesupport_introspection_c__Compute_Response_message_type_support_handle,
  &msgs__srv__Compute_Event__rosidl_typesupport_introspection_c__Compute_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    msgs,
    srv,
    Compute
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    msgs,
    srv,
    Compute
  ),
  &msgs__srv__Compute__get_type_hash,
  &msgs__srv__Compute__get_type_description,
  &msgs__srv__Compute__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute)(void) {
  if (!msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_type_support_handle.typesupport_identifier) {
    msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, Compute_Event)()->data;
  }

  return &msgs__srv__detail__compute__rosidl_typesupport_introspection_c__Compute_service_type_support_handle;
}
