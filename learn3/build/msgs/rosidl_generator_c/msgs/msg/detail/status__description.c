// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from msgs:msg/Status.idl
// generated code does not contain a copyright notice

#include "msgs/msg/detail/status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_type_hash_t *
msgs__msg__Status__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe8, 0xdb, 0x7e, 0x7f, 0xaf, 0x2f, 0x88, 0xcb,
      0xb2, 0x1b, 0xcd, 0xb0, 0x93, 0x96, 0x8b, 0x1e,
      0xe5, 0xaa, 0x99, 0x46, 0x62, 0x93, 0x84, 0x2c,
      0x16, 0x8b, 0x4b, 0xcd, 0xc5, 0xb3, 0xe9, 0xd6,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char msgs__msg__Status__TYPE_NAME[] = "msgs/msg/Status";

// Define type names, field names, and default values
static char msgs__msg__Status__FIELD_NAME__name[] = "name";
static char msgs__msg__Status__FIELD_NAME__level[] = "level";
static char msgs__msg__Status__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field msgs__msg__Status__FIELDS[] = {
  {
    {msgs__msg__Status__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {msgs__msg__Status__FIELD_NAME__level, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {msgs__msg__Status__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
msgs__msg__Status__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {msgs__msg__Status__TYPE_NAME, 15, 15},
      {msgs__msg__Status__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string name\n"
  "int32 level\n"
  "string message";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
msgs__msg__Status__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {msgs__msg__Status__TYPE_NAME, 15, 15},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 39, 39},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
msgs__msg__Status__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *msgs__msg__Status__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
