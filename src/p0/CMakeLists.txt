cmake_minimum_required(VERSION 3.8)
project(p0)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(p0_interfaces REQUIRED)

# add_executable(talker src/publisher_node.cpp)
# add_executable(ping src/ping.cpp)
# ament_target_dependencies(ping rclcpp std_msgs)
# ament_target_dependencies(talker rclcpp std_msgs)

# add_executable(listener src/subscriber_node.cpp)
# add_executable(pong src/pong.cpp)
# ament_target_dependencies(pong rclcpp std_msgs p0_interfaces)
# ament_target_dependencies(listener rclcpp std_msgs)

add_executable(status_robot src/status_publisher.cpp)
ament_target_dependencies(status_robot rclcpp std_msgs p0_interfaces)

# install(TARGETS talker DESTINATION lib/${PROJECT_NAME})
# install(TARGETS listener DESTINATION lib/${PROJECT_NAME})
# install(TARGETS ping DESTINATION lib/${PROJECT_NAME})
# install(TARGETS pong DESTINATION lib/${PROJECT_NAME})

install(TARGETS status_robot DESTINATION lib/${PROJECT_NAME})

ament_package()
