// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from p0_interfaces:srv/GetStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "p0_interfaces/srv/detail/get_status__rosidl_typesupport_introspection_c.h"
#include "p0_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "p0_interfaces/srv/detail/get_status__functions.h"
#include "p0_interfaces/srv/detail/get_status__struct.h"


// Include directives for member types
// Member `robot_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  p0_interfaces__srv__GetStatus_Request__init(message_memory);
}

void p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_fini_function(void * message_memory)
{
  p0_interfaces__srv__GetStatus_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_member_array[1] = {
  {
    "robot_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__srv__GetStatus_Request, robot_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_members = {
  "p0_interfaces__srv",  // message namespace
  "GetStatus_Request",  // message name
  1,  // number of fields
  sizeof(p0_interfaces__srv__GetStatus_Request),
  p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_member_array,  // message members
  p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_type_support_handle = {
  0,
  &p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_p0_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Request)() {
  if (!p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_type_support_handle.typesupport_identifier) {
    p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &p0_interfaces__srv__GetStatus_Request__rosidl_typesupport_introspection_c__GetStatus_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "p0_interfaces/srv/detail/get_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "p0_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "p0_interfaces/srv/detail/get_status__functions.h"
// already included above
// #include "p0_interfaces/srv/detail/get_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  p0_interfaces__srv__GetStatus_Response__init(message_memory);
}

void p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_fini_function(void * message_memory)
{
  p0_interfaces__srv__GetStatus_Response__fini(message_memory);
}

size_t p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__size_function__GetStatus_Response__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetStatus_Response__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_function__GetStatus_Response__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__fetch_function__GetStatus_Response__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetStatus_Response__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__assign_function__GetStatus_Response__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_function__GetStatus_Response__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_member_array[3] = {
  {
    "battery",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__srv__GetStatus_Response, battery),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__srv__GetStatus_Response, position),  // bytes offset in struct
    NULL,  // default value
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__size_function__GetStatus_Response__position,  // size() function pointer
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetStatus_Response__position,  // get_const(index) function pointer
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__get_function__GetStatus_Response__position,  // get(index) function pointer
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__fetch_function__GetStatus_Response__position,  // fetch(index, &value) function pointer
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__assign_function__GetStatus_Response__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "found",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__srv__GetStatus_Response, found),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_members = {
  "p0_interfaces__srv",  // message namespace
  "GetStatus_Response",  // message name
  3,  // number of fields
  sizeof(p0_interfaces__srv__GetStatus_Response),
  p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_member_array,  // message members
  p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_type_support_handle = {
  0,
  &p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_p0_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Response)() {
  if (!p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_type_support_handle.typesupport_identifier) {
    p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &p0_interfaces__srv__GetStatus_Response__rosidl_typesupport_introspection_c__GetStatus_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "p0_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "p0_interfaces/srv/detail/get_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_members = {
  "p0_interfaces__srv",  // service namespace
  "GetStatus",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_Request_message_type_support_handle,
  NULL  // response message
  // p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_Response_message_type_support_handle
};

static rosidl_service_type_support_t p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_type_support_handle = {
  0,
  &p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_p0_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus)() {
  if (!p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_type_support_handle.typesupport_identifier) {
    p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, srv, GetStatus_Response)()->data;
  }

  return &p0_interfaces__srv__detail__get_status__rosidl_typesupport_introspection_c__GetStatus_service_type_support_handle;
}
