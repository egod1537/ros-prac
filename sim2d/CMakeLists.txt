cmake_minimum_required(VERSION 3.20)
project(sim2d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sim2d STATIC
  src/sim.cpp
  src/sim_view.cpp
)

target_include_directories(sim2d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(sim2d PUBLIC cxx_std_17)

add_executable(sim2d_basic
  examples/basic_loop.cpp
)
target_link_libraries(sim2d_basic PRIVATE sim2d)

enable_testing()

add_executable(sim2d_smoke
  tests/smoke.cpp
)
target_link_libraries(sim2d_smoke PRIVATE sim2d)
add_test(NAME sim2d_smoke COMMAND sim2d_smoke)
