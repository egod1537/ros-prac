// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from msgs:srv/GetAverage.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "msgs/srv/detail/get_average__struct.h"
#include "msgs/srv/detail/get_average__type_support.h"
#include "msgs/srv/detail/get_average__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetAverage_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Request_type_support_ids_t;

static const _GetAverage_Request_type_support_ids_t _GetAverage_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetAverage_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetAverage_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetAverage_Request_type_support_symbol_names_t _GetAverage_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, msgs, srv, GetAverage_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, GetAverage_Request)),
  }
};

typedef struct _GetAverage_Request_type_support_data_t
{
  void * data[2];
} _GetAverage_Request_type_support_data_t;

static _GetAverage_Request_type_support_data_t _GetAverage_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetAverage_Request_message_typesupport_map = {
  2,
  "msgs",
  &_GetAverage_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GetAverage_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GetAverage_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetAverage_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Request__get_type_hash,
  &msgs__srv__GetAverage_Request__get_type_description,
  &msgs__srv__GetAverage_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, msgs, srv, GetAverage_Request)() {
  return &::msgs::srv::rosidl_typesupport_c::GetAverage_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "msgs/srv/detail/get_average__struct.h"
// already included above
// #include "msgs/srv/detail/get_average__type_support.h"
// already included above
// #include "msgs/srv/detail/get_average__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetAverage_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Response_type_support_ids_t;

static const _GetAverage_Response_type_support_ids_t _GetAverage_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetAverage_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetAverage_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetAverage_Response_type_support_symbol_names_t _GetAverage_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, msgs, srv, GetAverage_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, GetAverage_Response)),
  }
};

typedef struct _GetAverage_Response_type_support_data_t
{
  void * data[2];
} _GetAverage_Response_type_support_data_t;

static _GetAverage_Response_type_support_data_t _GetAverage_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetAverage_Response_message_typesupport_map = {
  2,
  "msgs",
  &_GetAverage_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GetAverage_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GetAverage_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetAverage_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Response__get_type_hash,
  &msgs__srv__GetAverage_Response__get_type_description,
  &msgs__srv__GetAverage_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, msgs, srv, GetAverage_Response)() {
  return &::msgs::srv::rosidl_typesupport_c::GetAverage_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "msgs/srv/detail/get_average__struct.h"
// already included above
// #include "msgs/srv/detail/get_average__type_support.h"
// already included above
// #include "msgs/srv/detail/get_average__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetAverage_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Event_type_support_ids_t;

static const _GetAverage_Event_type_support_ids_t _GetAverage_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetAverage_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetAverage_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetAverage_Event_type_support_symbol_names_t _GetAverage_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, msgs, srv, GetAverage_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, GetAverage_Event)),
  }
};

typedef struct _GetAverage_Event_type_support_data_t
{
  void * data[2];
} _GetAverage_Event_type_support_data_t;

static _GetAverage_Event_type_support_data_t _GetAverage_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetAverage_Event_message_typesupport_map = {
  2,
  "msgs",
  &_GetAverage_Event_message_typesupport_ids.typesupport_identifier[0],
  &_GetAverage_Event_message_typesupport_symbol_names.symbol_name[0],
  &_GetAverage_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetAverage_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Event__get_type_hash,
  &msgs__srv__GetAverage_Event__get_type_description,
  &msgs__srv__GetAverage_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, msgs, srv, GetAverage_Event)() {
  return &::msgs::srv::rosidl_typesupport_c::GetAverage_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "msgs/srv/detail/get_average__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _GetAverage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_type_support_ids_t;

static const _GetAverage_type_support_ids_t _GetAverage_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetAverage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetAverage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetAverage_type_support_symbol_names_t _GetAverage_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, msgs, srv, GetAverage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, srv, GetAverage)),
  }
};

typedef struct _GetAverage_type_support_data_t
{
  void * data[2];
} _GetAverage_type_support_data_t;

static _GetAverage_type_support_data_t _GetAverage_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetAverage_service_typesupport_map = {
  2,
  "msgs",
  &_GetAverage_service_typesupport_ids.typesupport_identifier[0],
  &_GetAverage_service_typesupport_symbol_names.symbol_name[0],
  &_GetAverage_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GetAverage_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &GetAverage_Request_message_type_support_handle,
  &GetAverage_Response_message_type_support_handle,
  &GetAverage_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    msgs,
    srv,
    GetAverage
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    msgs,
    srv,
    GetAverage
  ),
  &msgs__srv__GetAverage__get_type_hash,
  &msgs__srv__GetAverage__get_type_description,
  &msgs__srv__GetAverage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, msgs, srv, GetAverage)() {
  return &::msgs::srv::rosidl_typesupport_c::GetAverage_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
