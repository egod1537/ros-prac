cmake_minimum_required(VERSION 3.8)
project(nodes)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(heater src/heater.cpp)
ament_target_dependencies(heater rclcpp)

install(TARGETS heater
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config)
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)

ament_package()
