// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from msgs:srv/GetAverage.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "msgs/srv/detail/get_average__functions.h"
#include "msgs/srv/detail/get_average__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetAverage_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Request_type_support_ids_t;

static const _GetAverage_Request_type_support_ids_t _GetAverage_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, GetAverage_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, GetAverage_Request)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Request__get_type_hash,
  &msgs__srv__GetAverage_Request__get_type_description,
  &msgs__srv__GetAverage_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::GetAverage_Request>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::GetAverage_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, GetAverage_Request)() {
  return get_message_type_support_handle<msgs::srv::GetAverage_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "msgs/srv/detail/get_average__functions.h"
// already included above
// #include "msgs/srv/detail/get_average__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetAverage_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Response_type_support_ids_t;

static const _GetAverage_Response_type_support_ids_t _GetAverage_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, GetAverage_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, GetAverage_Response)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Response__get_type_hash,
  &msgs__srv__GetAverage_Response__get_type_description,
  &msgs__srv__GetAverage_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::GetAverage_Response>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::GetAverage_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, GetAverage_Response)() {
  return get_message_type_support_handle<msgs::srv::GetAverage_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "msgs/srv/detail/get_average__functions.h"
// already included above
// #include "msgs/srv/detail/get_average__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetAverage_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_Event_type_support_ids_t;

static const _GetAverage_Event_type_support_ids_t _GetAverage_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, GetAverage_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, GetAverage_Event)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__GetAverage_Event__get_type_hash,
  &msgs__srv__GetAverage_Event__get_type_description,
  &msgs__srv__GetAverage_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::GetAverage_Event>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::GetAverage_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, GetAverage_Event)() {
  return get_message_type_support_handle<msgs::srv::GetAverage_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "msgs/srv/detail/get_average__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetAverage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetAverage_type_support_ids_t;

static const _GetAverage_type_support_ids_t _GetAverage_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, GetAverage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, GetAverage)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetAverage_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::GetAverage_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::GetAverage_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::GetAverage_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<msgs::srv::GetAverage>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<msgs::srv::GetAverage>,
  &msgs__srv__GetAverage__get_type_hash,
  &msgs__srv__GetAverage__get_type_description,
  &msgs__srv__GetAverage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<msgs::srv::GetAverage>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::GetAverage_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, GetAverage)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<msgs::srv::GetAverage>();
}

#ifdef __cplusplus
}
#endif
