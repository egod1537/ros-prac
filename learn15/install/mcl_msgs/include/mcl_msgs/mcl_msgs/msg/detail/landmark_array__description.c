// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from mcl_msgs:msg/LandmarkArray.idl
// generated code does not contain a copyright notice

#include "mcl_msgs/msg/detail/landmark_array__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_mcl_msgs
const rosidl_type_hash_t *
mcl_msgs__msg__LandmarkArray__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xcd, 0x5b, 0x0a, 0x6c, 0x5c, 0x92, 0x11, 0xc5,
      0x7d, 0x05, 0x0f, 0xb5, 0xf2, 0xd6, 0x54, 0x91,
      0x78, 0x39, 0x35, 0x7d, 0xaa, 0x66, 0x56, 0x46,
      0x1b, 0x9d, 0x40, 0x2e, 0xe3, 0xa4, 0x48, 0x07,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "mcl_msgs/msg/detail/landmark__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t mcl_msgs__msg__Landmark__EXPECTED_HASH = {1, {
    0x89, 0x3f, 0x07, 0xff, 0x5b, 0xc5, 0xcd, 0x53,
    0x2b, 0xb1, 0xc1, 0x8b, 0x5f, 0x4e, 0xcc, 0x8f,
    0xe3, 0xfd, 0xae, 0x2b, 0x29, 0xa7, 0xd7, 0x30,
    0x41, 0xd5, 0x16, 0x22, 0xf0, 0x81, 0x04, 0x1d,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char mcl_msgs__msg__LandmarkArray__TYPE_NAME[] = "mcl_msgs/msg/LandmarkArray";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char mcl_msgs__msg__Landmark__TYPE_NAME[] = "mcl_msgs/msg/Landmark";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char mcl_msgs__msg__LandmarkArray__FIELD_NAME__header[] = "header";
static char mcl_msgs__msg__LandmarkArray__FIELD_NAME__landmarks[] = "landmarks";

static rosidl_runtime_c__type_description__Field mcl_msgs__msg__LandmarkArray__FIELDS[] = {
  {
    {mcl_msgs__msg__LandmarkArray__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {mcl_msgs__msg__LandmarkArray__FIELD_NAME__landmarks, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {mcl_msgs__msg__Landmark__TYPE_NAME, 21, 21},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription mcl_msgs__msg__LandmarkArray__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {mcl_msgs__msg__Landmark__TYPE_NAME, 21, 21},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mcl_msgs__msg__LandmarkArray__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mcl_msgs__msg__LandmarkArray__TYPE_NAME, 26, 26},
      {mcl_msgs__msg__LandmarkArray__FIELDS, 2, 2},
    },
    {mcl_msgs__msg__LandmarkArray__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&mcl_msgs__msg__Landmark__EXPECTED_HASH, mcl_msgs__msg__Landmark__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = mcl_msgs__msg__Landmark__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Header header\n"
  "Landmark[] landmarks";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
mcl_msgs__msg__LandmarkArray__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mcl_msgs__msg__LandmarkArray__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 44, 44},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mcl_msgs__msg__LandmarkArray__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mcl_msgs__msg__LandmarkArray__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *mcl_msgs__msg__Landmark__get_individual_type_description_source(NULL);
    sources[3] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
