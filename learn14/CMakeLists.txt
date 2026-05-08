cmake_minimum_required(VERSION 3.20)

project(learn14 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenMP REQUIRED)

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

set(LEARN14_SOURCES
  src/main.cpp
  src/sim/sim2d.cpp
  src/sim/sim_config.cpp
  src/sim/sim_view.cpp
)

add_executable(${PROJECT_NAME} ${LEARN14_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/sim
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Eigen3::Eigen
    imgui::imgui
    implot::implot
    OpenMP::OpenMP_CXX
)

if(EXISTS "${PROJECT_SOURCE_DIR}/src/omp_check.cpp")
  add_executable(omp_check src/omp_check.cpp)
  target_compile_features(omp_check PRIVATE cxx_std_17)
  target_link_libraries(omp_check PRIVATE OpenMP::OpenMP_CXX)
endif()
