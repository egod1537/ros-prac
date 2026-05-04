#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include "ekf2d.hpp"
#include "sim/sim2d.hpp"
#include "sim/sim_view.hpp"
#include <GLFW/glfw3.h>

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    fprintf(stderr, "glfwInit failed\n");
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *win =
      glfwCreateWindow(1280, 720, "EKF SLAM 1D", nullptr, nullptr);
  if (!win) {
    fprintf(stderr, "glfwCreateWindow failed\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(win);
  // glfwMaximizeWindow(win);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  SimView view(win);
  while (!glfwWindowShouldClose(win)) {
    view.render();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();
  glfwDestroyWindow(win);
  glfwTerminate();

  return 0;
}
