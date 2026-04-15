// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from msgs:srv/Compute.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "msgs/srv/detail/compute__functions.h"
#include "msgs/srv/detail/compute__struct.hpp"
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

typedef struct _Compute_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Compute_Request_type_support_ids_t;

static const _Compute_Request_type_support_ids_t _Compute_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Compute_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Compute_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Compute_Request_type_support_symbol_names_t _Compute_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, Compute_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, Compute_Request)),
  }
};

typedef struct _Compute_Request_type_support_data_t
{
  void * data[2];
} _Compute_Request_type_support_data_t;

static _Compute_Request_type_support_data_t _Compute_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Compute_Request_message_typesupport_map = {
  2,
  "msgs",
  &_Compute_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Compute_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Compute_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Compute_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Compute_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__Compute_Request__get_type_hash,
  &msgs__srv__Compute_Request__get_type_description,
  &msgs__srv__Compute_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::Compute_Request>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::Compute_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, Compute_Request)() {
  return get_message_type_support_handle<msgs::srv::Compute_Request>();
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
// #include "msgs/srv/detail/compute__functions.h"
// already included above
// #include "msgs/srv/detail/compute__struct.hpp"
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

typedef struct _Compute_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Compute_Response_type_support_ids_t;

static const _Compute_Response_type_support_ids_t _Compute_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Compute_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Compute_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Compute_Response_type_support_symbol_names_t _Compute_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, Compute_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, Compute_Response)),
  }
};

typedef struct _Compute_Response_type_support_data_t
{
  void * data[2];
} _Compute_Response_type_support_data_t;

static _Compute_Response_type_support_data_t _Compute_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Compute_Response_message_typesupport_map = {
  2,
  "msgs",
  &_Compute_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Compute_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Compute_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Compute_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Compute_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__Compute_Response__get_type_hash,
  &msgs__srv__Compute_Response__get_type_description,
  &msgs__srv__Compute_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::Compute_Response>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::Compute_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, Compute_Response)() {
  return get_message_type_support_handle<msgs::srv::Compute_Response>();
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
// #include "msgs/srv/detail/compute__functions.h"
// already included above
// #include "msgs/srv/detail/compute__struct.hpp"
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

typedef struct _Compute_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Compute_Event_type_support_ids_t;

static const _Compute_Event_type_support_ids_t _Compute_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Compute_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Compute_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Compute_Event_type_support_symbol_names_t _Compute_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, Compute_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, Compute_Event)),
  }
};

typedef struct _Compute_Event_type_support_data_t
{
  void * data[2];
} _Compute_Event_type_support_data_t;

static _Compute_Event_type_support_data_t _Compute_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Compute_Event_message_typesupport_map = {
  2,
  "msgs",
  &_Compute_Event_message_typesupport_ids.typesupport_identifier[0],
  &_Compute_Event_message_typesupport_symbol_names.symbol_name[0],
  &_Compute_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Compute_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Compute_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &msgs__srv__Compute_Event__get_type_hash,
  &msgs__srv__Compute_Event__get_type_description,
  &msgs__srv__Compute_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<msgs::srv::Compute_Event>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::Compute_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, Compute_Event)() {
  return get_message_type_support_handle<msgs::srv::Compute_Event>();
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
// #include "msgs/srv/detail/compute__struct.hpp"
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

typedef struct _Compute_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Compute_type_support_ids_t;

static const _Compute_type_support_ids_t _Compute_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Compute_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Compute_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Compute_type_support_symbol_names_t _Compute_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, msgs, srv, Compute)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, msgs, srv, Compute)),
  }
};

typedef struct _Compute_type_support_data_t
{
  void * data[2];
} _Compute_type_support_data_t;

static _Compute_type_support_data_t _Compute_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Compute_service_typesupport_map = {
  2,
  "msgs",
  &_Compute_service_typesupport_ids.typesupport_identifier[0],
  &_Compute_service_typesupport_symbol_names.symbol_name[0],
  &_Compute_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Compute_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Compute_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::Compute_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::Compute_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<msgs::srv::Compute_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<msgs::srv::Compute>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<msgs::srv::Compute>,
  &msgs__srv__Compute__get_type_hash,
  &msgs__srv__Compute__get_type_description,
  &msgs__srv__Compute__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<msgs::srv::Compute>()
{
  return &::msgs::srv::rosidl_typesupport_cpp::Compute_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, msgs, srv, Compute)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<msgs::srv::Compute>();
}

#ifdef __cplusplus
}
#endif
