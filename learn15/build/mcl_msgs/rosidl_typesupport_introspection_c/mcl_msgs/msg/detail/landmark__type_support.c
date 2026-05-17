// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mcl_msgs/msg/detail/landmark__rosidl_typesupport_introspection_c.h"
#include "mcl_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mcl_msgs/msg/detail/landmark__functions.h"
#include "mcl_msgs/msg/detail/landmark__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mcl_msgs__msg__Landmark__init(message_memory);
}

void mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_fini_function(void * message_memory)
{
  mcl_msgs__msg__Landmark__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_member_array[3] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs__msg__Landmark, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "range",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs__msg__Landmark, range),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "bearing",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs__msg__Landmark, bearing),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_members = {
  "mcl_msgs__msg",  // message namespace
  "Landmark",  // message name
  3,  // number of fields
  sizeof(mcl_msgs__msg__Landmark),
  false,  // has_any_key_member_
  mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_member_array,  // message members
  mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_init_function,  // function to initialize message memory (memory has to be allocated)
  mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle = {
  0,
  &mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_members,
  get_message_typesupport_handle_function,
  &mcl_msgs__msg__Landmark__get_type_hash,
  &mcl_msgs__msg__Landmark__get_type_description,
  &mcl_msgs__msg__Landmark__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mcl_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mcl_msgs, msg, Landmark)() {
  if (!mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle.typesupport_identifier) {
    mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mcl_msgs__msg__Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
