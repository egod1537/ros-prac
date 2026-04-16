cmake_minimum_required(VERSION 3.8)
project(nodes)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(msgs REQUIRED)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp msgs)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp msgs)

install(TARGETS talker listener
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch/ 
  DESTINATION share/${PROJECT_NAME}/launch)

ament_package()
