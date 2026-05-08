cmake_minimum_required(VERSION 3.20)
project(learn13 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenMP REQUIRED)

include(FetchContent)
FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.9
)
FetchContent_Declare(implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG v0.16
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

target_include_directories(imgui
  PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

add_library(implot
  STATIC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
)
target_include_directories(implot PUBLIC ${implot_SOURCE_DIR})
target_link_libraries(implot PUBLIC imgui)

add_executable(learn13
  src/main.cpp
  src/sim/sim_config.cpp
  src/sim/sim2d.cpp
  src/sim/sim_view.cpp
  src/mcl.cpp
  src/mcl_omp.cpp
  src/timing.cpp
)
add_executable(omp_check src/omp_check.cpp)

target_include_directories(learn13 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sim
)

target_link_libraries(learn13 PRIVATE
  Eigen3::Eigen
  imgui implot
  OpenMP::OpenMP_CXX
)
target_link_libraries(omp_check PRIVATE OpenMP::OpenMP_CXX)
