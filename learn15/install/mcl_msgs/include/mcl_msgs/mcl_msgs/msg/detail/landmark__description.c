// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

#include "mcl_msgs/msg/detail/landmark__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_mcl_msgs
const rosidl_type_hash_t *
mcl_msgs__msg__Landmark__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x89, 0x3f, 0x07, 0xff, 0x5b, 0xc5, 0xcd, 0x53,
      0x2b, 0xb1, 0xc1, 0x8b, 0x5f, 0x4e, 0xcc, 0x8f,
      0xe3, 0xfd, 0xae, 0x2b, 0x29, 0xa7, 0xd7, 0x30,
      0x41, 0xd5, 0x16, 0x22, 0xf0, 0x81, 0x04, 0x1d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char mcl_msgs__msg__Landmark__TYPE_NAME[] = "mcl_msgs/msg/Landmark";

// Define type names, field names, and default values
static char mcl_msgs__msg__Landmark__FIELD_NAME__id[] = "id";
static char mcl_msgs__msg__Landmark__FIELD_NAME__range[] = "range";
static char mcl_msgs__msg__Landmark__FIELD_NAME__bearing[] = "bearing";

static rosidl_runtime_c__type_description__Field mcl_msgs__msg__Landmark__FIELDS[] = {
  {
    {mcl_msgs__msg__Landmark__FIELD_NAME__id, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mcl_msgs__msg__Landmark__FIELD_NAME__range, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mcl_msgs__msg__Landmark__FIELD_NAME__bearing, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mcl_msgs__msg__Landmark__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mcl_msgs__msg__Landmark__TYPE_NAME, 21, 21},
      {mcl_msgs__msg__Landmark__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 id\n"
  "float64 range\n"
  "float64 bearing";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
mcl_msgs__msg__Landmark__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mcl_msgs__msg__Landmark__TYPE_NAME, 21, 21},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 39, 39},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mcl_msgs__msg__Landmark__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mcl_msgs__msg__Landmark__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
