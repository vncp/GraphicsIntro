#include "menu.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

Menu::Menu(GLFWwindow *window, EventHandler *eventHandler)
  : m_window(window),
  m_eventHandler(eventHandler),
  m_menuHovered(false),
  m_spinMultiplier(1.0f),
  m_orbitMultiplier(1.0f),
  m_reverseSpinDirection(false),
  m_reverseOrbitDirection(false),
  m_toggleOrbit(false),
  m_toggleSpin(false)
{
  // Subscribe event handlers so checkboxes sync with key presses
  m_eventHandler->subscribe(GLFW_KEY_A, this);
  m_eventHandler->subscribe(GLFW_KEY_S, this);
  m_eventHandler->subscribe(GLFW_KEY_X, this);
  m_eventHandler->subscribe(GLFW_KEY_Z, this);
  m_eventHandler->subscribe(GLFW_MOUSE_BUTTON_LEFT, this);

  // ImGui Setup
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  m_io = ImGui::GetIO();
  // Avoid unused variable errors
  (void)m_io;

  // ImGui Config
  m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();

  // ImGui Init Backends
  const char* glsl_version = "#version 330";
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

Menu::~Menu()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  m_window = nullptr;
}

void Menu::refresh() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  {
    ImGui::Begin("Controls");

    m_menuHovered = ImGui::IsWindowHovered();

    if (ImGui::Checkbox("Toggle - Spin Direction", &m_reverseSpinDirection)){
      m_reverseSpinDirection = !m_reverseSpinDirection;
      m_eventHandler->notify(GLFW_KEY_A);
    }
    if (ImGui::Checkbox("Toggle - Orbit Direction", &m_reverseOrbitDirection)){
      m_reverseOrbitDirection = !m_reverseOrbitDirection;
      m_eventHandler->notify(GLFW_KEY_S);
    }
    if (ImGui::Checkbox("Toggle - Orbit Off", &m_toggleOrbit)){
      m_toggleOrbit = !m_toggleOrbit;
      m_eventHandler->notify(GLFW_KEY_X);
    }
    if (ImGui::Checkbox("Toggle - Spin Off", &m_toggleSpin)){
      m_toggleSpin = !m_toggleSpin;
      m_eventHandler->notify(GLFW_KEY_Z);
    }
    if (ImGui::SliderFloat("Spin Speed", &m_spinMultiplier, 0.0f, 5.0f)) {
      // define enum later
      m_eventHandler->notify<float>(-1, &m_spinMultiplier);
    }
    if (ImGui::SliderFloat("Orbit Speed", &m_orbitMultiplier, 0.0f, 5.0f)) {
      m_eventHandler->notify<float>(-2, &m_orbitMultiplier);
    }
    ImGui::Text("Keybinds");
    ImGui::Text("[A] - Toggle Spin Direction");
    ImGui::Text("[S] - Toggle Orbit Direction");
    ImGui::Text("[X] - Toggle Orbit");
    ImGui::Text("[Z] - Toggle Spin");

    ImGui::Text("Statistics");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }
  // Render
  ImGui::Render();
}

void Menu::renderDrawData()
{
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Update events
void Menu::handleEvent(int key)
{
  switch (key)
  {
    case GLFW_MOUSE_BUTTON_LEFT:
    case GLFW_KEY_A:
      m_reverseSpinDirection = !m_reverseSpinDirection;
      break;
    case GLFW_KEY_S:
      m_reverseOrbitDirection = !m_reverseOrbitDirection;
      break;
    case GLFW_KEY_X:
      m_toggleOrbit = !m_toggleOrbit;
      break;
    case GLFW_KEY_Z:
      m_toggleSpin = !m_toggleSpin;
      break;
  }
}

void Menu::handleEvent(int key, float *val)
{
}
