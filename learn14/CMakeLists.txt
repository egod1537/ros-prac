cmake_minimum_required(VERSION 3.20)

project(learn14 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.9
  GIT_SHALLOW TRUE
)

FetchContent_Declare(
  implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG v0.16
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui implot)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui::imgui ALIAS imgui)

target_compile_features(imgui PUBLIC cxx_std_17)
target_include_directories(imgui
  SYSTEM PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui
  PUBLIC
    glfw
    OpenGL::GL
)

add_library(implot STATIC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
)
add_library(implot::implot ALIAS implot)

target_compile_features(implot PUBLIC cxx_std_17)
target_include_directories(implot SYSTEM PUBLIC ${implot_SOURCE_DIR})
target_link_libraries(implot PUBLIC imgui::imgui)

add_library(fastslam_core STATIC
  src/fastslam.cpp
  src/particle.cpp
  src/sim/sim_config.cpp
)
add_library(fastslam::core ALIAS fastslam_core)

target_compile_features(fastslam_core PUBLIC cxx_std_17)
target_include_directories(fastslam_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/sim
)
target_link_libraries(fastslam_core PUBLIC Eigen3::Eigen)

set(FASTSLAM_SIM_SOURCES
  src/main.cpp
  src/sim_view.cpp
)

add_executable(fastslam_sim ${FASTSLAM_SIM_SOURCES})
add_executable(${PROJECT_NAME} ALIAS fastslam_sim)
set_target_properties(fastslam_sim PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_compile_features(fastslam_sim PRIVATE cxx_std_17)
target_include_directories(fastslam_sim
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/sim
)
target_link_libraries(fastslam_sim
  PRIVATE
    fastslam::core
    imgui::imgui
    implot::implot
    glfw
    OpenGL::GL
)

add_executable(learn14_benchmark
  src/benchmark_view.cpp
  src/benchmark.cpp
)

target_compile_features(learn14_benchmark PRIVATE cxx_std_17)
target_link_libraries(learn14_benchmark
  PRIVATE
    fastslam::core
    imgui::imgui
    implot::implot
    glfw
    OpenGL::GL
    Threads::Threads
)
