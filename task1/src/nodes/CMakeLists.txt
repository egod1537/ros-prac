cmake_minimum_required(VERSION 3.8)
project(nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(msgs REQUIRED)

add_executable(sensor src/sensor.cpp)
add_executable(monitor src/monitor.cpp)

ament_target_dependencies(sensor rclcpp msgs)
ament_target_dependencies(monitor rclcpp msgs)

target_include_directories(sensor PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(sensor PUBLIC c_std_99 cxx_std_17)

install(TARGETS sensor
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS sensor monitor
  DESTINATION lib/${PROJECT_NAME})
ament_package()
