// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "mcl_msgs/msg/detail/landmark__functions.h"
#include "mcl_msgs/msg/detail/landmark__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace mcl_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Landmark_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) mcl_msgs::msg::Landmark(_init);
}

void Landmark_fini_function(void * message_memory)
{
  auto typed_message = static_cast<mcl_msgs::msg::Landmark *>(message_memory);
  typed_message->~Landmark();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Landmark_message_member_array[3] = {
  {
    "id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs::msg::Landmark, id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "range",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs::msg::Landmark, range),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "bearing",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mcl_msgs::msg::Landmark, bearing),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Landmark_message_members = {
  "mcl_msgs::msg",  // message namespace
  "Landmark",  // message name
  3,  // number of fields
  sizeof(mcl_msgs::msg::Landmark),
  false,  // has_any_key_member_
  Landmark_message_member_array,  // message members
  Landmark_init_function,  // function to initialize message memory (memory has to be allocated)
  Landmark_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Landmark_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Landmark_message_members,
  get_message_typesupport_handle_function,
  &mcl_msgs__msg__Landmark__get_type_hash,
  &mcl_msgs__msg__Landmark__get_type_description,
  &mcl_msgs__msg__Landmark__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace mcl_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<mcl_msgs::msg::Landmark>()
{
  return &::mcl_msgs::msg::rosidl_typesupport_introspection_cpp::Landmark_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mcl_msgs, msg, Landmark)() {
  return &::mcl_msgs::msg::rosidl_typesupport_introspection_cpp::Landmark_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
