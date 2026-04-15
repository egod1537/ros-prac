cmake_minimum_required(VERSION 3.8)
project(nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(msgs REQUIRED)

add_executable(talker src/talker.cpp)
add_executable(listener src/listener.cpp)
add_executable(calc_server src/calc_server.cpp)

ament_target_dependencies(talker rclcpp msgs)
ament_target_dependencies(listener rclcpp msgs)
ament_target_dependencies(calc_server rclcpp msgs)

target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(talker PUBLIC c_std_99 cxx_std_17)

install(TARGETS listener 
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS talker
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS talker listener calc_server 
  DESTINATION lib/${PROJECT_NAME})

ament_package()
