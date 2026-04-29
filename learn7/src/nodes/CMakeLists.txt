cmake_minimum_required(VERSION 3.8)
project(nodes)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(DEPS rclcpp tf2 tf2_ros tf2_geometry_msgs geometry_msgs)

add_executable(static_broadcaster src/static_broadcaster.cpp)
ament_target_dependencies(static_broadcaster ${DEPS})

add_executable(mover src/mover.cpp)
ament_target_dependencies(mover ${DEPS})

add_executable(tracker src/tracker.cpp)
ament_target_dependencies(tracker ${DEPS})

install(TARGETS static_broadcaster mover tracker
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)

ament_package()
