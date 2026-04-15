cmake_minimum_required(VERSION 3.8)
project(pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(publisher src/publisher.cpp)
add_executable(subscriber src/subscriber.cpp)
target_include_directories(publisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(publisher PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(publisher rclcpp std_msgs)
ament_target_dependencies(subscriber rclcpp std_msgs)


install(TARGETS publisher
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS subscriber 
  DESTINATION lib/${PROJECT_NAME})

ament_package()
