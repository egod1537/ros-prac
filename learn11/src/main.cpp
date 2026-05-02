#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include "ekf.hpp"
#include "sim.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

struct SimConfig {
  float sigma_u = 0.3f;
  float sigma_z = 0.5f;

  std::vector<float> landmark_pos = {3.0f, 7.0f, 12.0f};
};

class Sim {
public:
  SimState state;
  EKF ekf;

  Sim() : ekf(0.0, 0.0) {}

  void init(const SimConfig &config) {
    state.true_robot_pos = 0.0;
    state.true_landmark_pos.assign(config.landmark_pos.begin(),
                                   config.landmark_pos.end());
    state.time = 0.0;

    ekf = EKF(config.sigma_u, config.sigma_z);
  }

  void step(float step_u) {
    sim_move(state, step_u, ekf.sigma_u);
    ekf.predict(step_u);

    int landmark_size = state.get_landmark_count();
    for (int i = 0; i < landmark_size; i++) {
      double z = sim_measure(state, i, ekf.sigma_z);
      ekf.observe(i, z);
    }

    state.time += 1.0;
  }
};

class SimView {
public:
  SimView(GLFWwindow *win) : win_(win), sim_() { sim_.init(config_); }

  void render() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    render_config();
    render_control();
    render_space();

    present_frame();
  }

private:
  void render_config() {
    ImGui::Begin("Config");

    ImGui::SliderFloat("sigma_u", &config_.sigma_u, 1e-3, 1.0f);
    ImGui::SliderFloat("sigma_z", &config_.sigma_z, 1e-3, 1.0f);

    ImGui::Separator();
    ImGui::Text("Landmarks");
    for (size_t i = 0; i < config_.landmark_pos.size(); i++) {
      ImGui::PushID((int)i);
      ImGui::SliderFloat("##lm", &config_.landmark_pos[i], -20.0f, 20.0f);
      ImGui::PopID();
    }
    if (ImGui::Button("Add LM")) {
      config_.landmark_pos.push_back(0.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove LM") && !config_.landmark_pos.empty()) {
      config_.landmark_pos.pop_back();
    }

    ImGui::Separator();
    if (ImGui::Button("Apply & Reset")) {
      sim_.init(config_);
    }
    ImGui::End();
  }

  void render_control() {
    ImGui::Begin("EKF Control");
    ImGui::SliderFloat("step u", &step_u_, -1.0f, 1.0f);
    if (ImGui::Button("Step")) {
      sim_.step(step_u_);
    }
    ImGui::Text("True pos: %.3f", sim_.state.true_robot_pos);
    ImGui::Text("EKF pos:  %.3f ± %.3f", sim_.ekf.robot(),
                std::sqrt(sim_.ekf.robot_var()));

    int landmark_size = (int)sim_.state.true_landmark_pos.size();
    for (int i = 0; i < landmark_size; i++) {
      if (sim_.ekf.is_seen(i)) {
        ImGui::Text("LM%d: true=%.2f  est=%.2f ± %.2f", i,
                    sim_.state.true_landmark_pos[i], sim_.ekf.landmark(i),
                    std::sqrt(sim_.ekf.landmark_var(i)));
      }
    }
    ImGui::End();
  }

  void render_space() {
    ImGui::Begin("1D Space");
    if (ImPlot::BeginPlot("##space", ImVec2(-1, 200))) {
      ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_AutoFit,
                        ImPlotAxisFlags_AutoFit);

      float rx = (float)sim_.state.true_robot_pos, ry = 0.0f;
      ImPlot::PlotScatter("robot(true)", &rx, &ry, 1);

      int n = (int)sim_.state.true_landmark_pos.size();
      for (int i = 0; i < n; i++) {
        float lx = (float)sim_.state.true_landmark_pos[i], ly = 0.0f;
        ImPlot::PlotScatter("lm(true)", &lx, &ly, 1);
      }
      float ex = (float)sim_.ekf.robot(), ey = 0.5f;
      ImPlot::PlotScatter("robot(ekf)", &ex, &ey, 1);
      ImPlot::EndPlot();
    }
    ImGui::End();
  }

  void present_frame() {
    ImGui::Render();
    int w, h;
    glfwGetFramebufferSize(win_, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(win_);
  }

  Sim sim_;
  SimConfig config_;
  float step_u_ = 0.5f;
  GLFWwindow *win_;
};

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
