cmake_minimum_required(VERSION 3.8)
project(learn15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(mcl_msgs REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(mcl_core SHARED src/mcl.cpp)
target_include_directories(mcl_core PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)
target_link_libraries(mcl_core PUBLIC Eigen3::Eigen)

add_executable(mcl src/ros/mcl_node.cpp)
target_link_libraries(mcl PUBLIC
  mcl_core
  rclcpp::rclcpp
  ${nav_msgs_TARGETS}
  ${geometry_msgs_TARGETS}
  ${mcl_msgs_TARGETS}
  tf2::tf2
  tf2_ros::tf2_ros
  tf2_geometry_msgs::tf2_geometry_msgs
)

# add_executable(sim2d src/ros/sim2d_node.cpp)
# target_link_libraries(sim2d PUBLIC
#   mcl_core
#   rclcpp::rclcpp
#   ${nav_msgs_TARGETS}
#   ${geometry_msgs_TARGETS}
#   ${mcl_msgs_TARGETS}
#   tf2::tf2
#   tf2_ros::tf2_ros
# )
install(TARGETS mcl_core
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin
)
install(TARGETS mcl DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rclcpp std_msgs nav_msgs geometry_msgs
  tf2 tf2_ros tf2_geometry_msgs mcl_msgs Eigen3
)

ament_package()
