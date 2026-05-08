#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "mcl.hpp"
#include "mcl_omp.hpp"
#include "sim/sim_config.hpp"
#include "sim/sim_view.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  if (!glfwInit()) {
    std::fprintf(stderr, "glfwInit failed\n");
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *win =
      glfwCreateWindow(1280, 720, "MCL Localization 2D", nullptr, nullptr);
  if (!win) {
    std::fprintf(stderr, "glfwCreateWindow failed\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(win);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  SimConfig config;
  sim_config::load(config);
  sim_config::sanitize(config);

  Sim2D sim;
  sim.init(config);

  MCL mcl(config.sigma_v, config.sigma_w, config.sigma_r, config.sigma_phi,
          /*seed=*/42);
  MCL_OMP mcl_omp(config.sigma_v, config.sigma_w, config.sigma_r,
                  config.sigma_phi, /*seed=*/43);
  mcl.max_range = config.max_range;
  mcl_omp.max_range = config.max_range;
  mcl.known_map.assign(sim.true_landmarks.begin(), sim.true_landmarks.end());
  mcl_omp.known_map.assign(sim.true_landmarks.begin(),
                           sim.true_landmarks.end());
  mcl.init_gaussian(/*M=*/500, 0.0, 0.0, 0.0, 0.1);
  mcl_omp.init_gaussian(/*M=*/500, 0.0, 0.0, 0.0, 0.1);

  SimView view(win, sim, mcl, mcl_omp, config);
  while (!glfwWindowShouldClose(win))
    view.render();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();
  glfwDestroyWindow(win);
  glfwTerminate();

  return 0;
}
