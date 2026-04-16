cmake_minimum_required(VERSION 3.8)
project(nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(msgs REQUIRED)
find_package(rclcpp_action REQUIRED)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

ament_target_dependencies(server rclcpp rclcpp_action msgs)
ament_target_dependencies(client rclcpp rclcpp_action msgs)

target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(server PUBLIC c_std_99 cxx_std_17)  

install(TARGETS server
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS server client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
