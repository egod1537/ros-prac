// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from p0_interfaces:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef P0_INTERFACES__SRV__DETAIL__GET_STATUS__TRAITS_HPP_
#define P0_INTERFACES__SRV__DETAIL__GET_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "p0_interfaces/srv/detail/get_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace p0_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStatus_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_name
  {
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStatus_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace p0_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use p0_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const p0_interfaces::srv::GetStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  p0_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use p0_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const p0_interfaces::srv::GetStatus_Request & msg)
{
  return p0_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<p0_interfaces::srv::GetStatus_Request>()
{
  return "p0_interfaces::srv::GetStatus_Request";
}

template<>
inline const char * name<p0_interfaces::srv::GetStatus_Request>()
{
  return "p0_interfaces/srv/GetStatus_Request";
}

template<>
struct has_fixed_size<p0_interfaces::srv::GetStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<p0_interfaces::srv::GetStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<p0_interfaces::srv::GetStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace p0_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStatus_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: battery
  {
    out << "battery: ";
    rosidl_generator_traits::value_to_yaml(msg.battery, out);
    out << ", ";
  }

  // member: position
  {
    if (msg.position.size() == 0) {
      out << "position: []";
    } else {
      out << "position: [";
      size_t pending_items = msg.position.size();
      for (auto item : msg.position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: found
  {
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: battery
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery: ";
    rosidl_generator_traits::value_to_yaml(msg.battery, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: found
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStatus_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace p0_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use p0_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const p0_interfaces::srv::GetStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  p0_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use p0_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const p0_interfaces::srv::GetStatus_Response & msg)
{
  return p0_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<p0_interfaces::srv::GetStatus_Response>()
{
  return "p0_interfaces::srv::GetStatus_Response";
}

template<>
inline const char * name<p0_interfaces::srv::GetStatus_Response>()
{
  return "p0_interfaces/srv/GetStatus_Response";
}

template<>
struct has_fixed_size<p0_interfaces::srv::GetStatus_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<p0_interfaces::srv::GetStatus_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<p0_interfaces::srv::GetStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<p0_interfaces::srv::GetStatus>()
{
  return "p0_interfaces::srv::GetStatus";
}

template<>
inline const char * name<p0_interfaces::srv::GetStatus>()
{
  return "p0_interfaces/srv/GetStatus";
}

template<>
struct has_fixed_size<p0_interfaces::srv::GetStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<p0_interfaces::srv::GetStatus_Request>::value &&
    has_fixed_size<p0_interfaces::srv::GetStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<p0_interfaces::srv::GetStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<p0_interfaces::srv::GetStatus_Request>::value &&
    has_bounded_size<p0_interfaces::srv::GetStatus_Response>::value
  >
{
};

template<>
struct is_service<p0_interfaces::srv::GetStatus>
  : std::true_type
{
};

template<>
struct is_service_request<p0_interfaces::srv::GetStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<p0_interfaces::srv::GetStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // P0_INTERFACES__SRV__DETAIL__GET_STATUS__TRAITS_HPP_
