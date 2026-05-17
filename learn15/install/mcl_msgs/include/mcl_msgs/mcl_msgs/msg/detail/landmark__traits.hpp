// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mcl_msgs:msg/Landmark.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mcl_msgs/msg/landmark.hpp"


#ifndef MCL_MSGS__MSG__DETAIL__LANDMARK__TRAITS_HPP_
#define MCL_MSGS__MSG__DETAIL__LANDMARK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mcl_msgs/msg/detail/landmark__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace mcl_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Landmark & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: range
  {
    out << "range: ";
    rosidl_generator_traits::value_to_yaml(msg.range, out);
    out << ", ";
  }

  // member: bearing
  {
    out << "bearing: ";
    rosidl_generator_traits::value_to_yaml(msg.bearing, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Landmark & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: range
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "range: ";
    rosidl_generator_traits::value_to_yaml(msg.range, out);
    out << "\n";
  }

  // member: bearing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bearing: ";
    rosidl_generator_traits::value_to_yaml(msg.bearing, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Landmark & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace mcl_msgs

namespace rosidl_generator_traits
{

[[deprecated("use mcl_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mcl_msgs::msg::Landmark & msg,
  std::ostream & out, size_t indentation = 0)
{
  mcl_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mcl_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const mcl_msgs::msg::Landmark & msg)
{
  return mcl_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mcl_msgs::msg::Landmark>()
{
  return "mcl_msgs::msg::Landmark";
}

template<>
inline const char * name<mcl_msgs::msg::Landmark>()
{
  return "mcl_msgs/msg/Landmark";
}

template<>
struct has_fixed_size<mcl_msgs::msg::Landmark>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<mcl_msgs::msg::Landmark>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<mcl_msgs::msg::Landmark>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MCL_MSGS__MSG__DETAIL__LANDMARK__TRAITS_HPP_
