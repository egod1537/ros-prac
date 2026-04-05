// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from p0_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "p0_interfaces/msg/detail/robot_status__rosidl_typesupport_introspection_c.h"
#include "p0_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "p0_interfaces/msg/detail/robot_status__functions.h"
#include "p0_interfaces/msg/detail/robot_status__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  p0_interfaces__msg__RobotStatus__init(message_memory);
}

void p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_fini_function(void * message_memory)
{
  p0_interfaces__msg__RobotStatus__fini(message_memory);
}

size_t p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__size_function__RobotStatus__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__fetch_function__RobotStatus__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__assign_function__RobotStatus__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[4] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__msg__RobotStatus, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__msg__RobotStatus, battery),  // bytes offset in struct
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
    offsetof(p0_interfaces__msg__RobotStatus, position),  // bytes offset in struct
    NULL,  // default value
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__size_function__RobotStatus__position,  // size() function pointer
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__position,  // get_const(index) function pointer
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__position,  // get(index) function pointer
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__fetch_function__RobotStatus__position,  // fetch(index, &value) function pointer
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__assign_function__RobotStatus__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_active",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(p0_interfaces__msg__RobotStatus, is_active),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_members = {
  "p0_interfaces__msg",  // message namespace
  "RobotStatus",  // message name
  4,  // number of fields
  sizeof(p0_interfaces__msg__RobotStatus),
  p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array,  // message members
  p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle = {
  0,
  &p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_p0_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, p0_interfaces, msg, RobotStatus)() {
  if (!p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle.typesupport_identifier) {
    p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &p0_interfaces__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
