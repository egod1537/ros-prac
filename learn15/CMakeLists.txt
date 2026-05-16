cmake_minimum_required(VERSION 3.20)
project(learn15 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Eigen3 REQUIRED)

add_executable(learn15
  src/main.cpp
  src/mcl.cpp
)

target_include_directories(learn15 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(learn15 PRIVATE Eigen3::Eigen)
