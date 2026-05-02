cmake_minimum_required(VERSION 3.20)
project(learn11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG         v1.91.9
)

FetchContent_Declare(implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG         v0.16
)
FetchContent_MakeAvailable(imgui implot)

find_package(Eigen3 REQUIRED)

set(IMGUI_SRC
 ${imgui_SOURCE_DIR}/imgui.cpp
 ${imgui_SOURCE_DIR}/imgui_draw.cpp
 ${imgui_SOURCE_DIR}/imgui_tables.cpp
 ${imgui_SOURCE_DIR}/imgui_widgets.cpp
 ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
 ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

set(IMPLOT_SRC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
)

add_executable(learn11
  src/main.cpp
  src/ekf.cpp
  src/sim.cpp
  ${IMGUI_SRC}
  ${IMPLOT_SRC}
)

target_include_directories(learn11 PRIVATE
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
  ${implot_SOURCE_DIR}
  src/
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(learn11
  OpenGL::GL
  glfw
  Eigen3::Eigen
)
