// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from mcl_msgs:msg/LandmarkArray.idl
// generated code does not contain a copyright notice
#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "mcl_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mcl_msgs/msg/detail/landmark_array__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
bool cdr_serialize_mcl_msgs__msg__LandmarkArray(
  const mcl_msgs__msg__LandmarkArray * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
bool cdr_deserialize_mcl_msgs__msg__LandmarkArray(
  eprosima::fastcdr::Cdr &,
  mcl_msgs__msg__LandmarkArray * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
size_t get_serialized_size_mcl_msgs__msg__LandmarkArray(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
size_t max_serialized_size_mcl_msgs__msg__LandmarkArray(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
bool cdr_serialize_key_mcl_msgs__msg__LandmarkArray(
  const mcl_msgs__msg__LandmarkArray * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
size_t get_serialized_size_key_mcl_msgs__msg__LandmarkArray(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
size_t max_serialized_size_key_mcl_msgs__msg__LandmarkArray(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mcl_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mcl_msgs, msg, LandmarkArray)();

#ifdef __cplusplus
}
#endif

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
