#ifndef __MENU_H__
#define __MENU_H__

#include "imgui.h"
#include "argwrapper.h"
#include "graphics_headers.h"
#include "eventhandler.h"

// Override Listener from eventhandler.h
class Menu : public Listener
{
public:
  Menu(GLFWwindow *window, EventHandler *eventHandler);
  ~Menu();
  void refresh();
  void renderDrawData();
  void handleEvent(int key);
  void handleEvent(int key, float *val);
  bool m_menuHovered;
private:
  GLFWwindow *m_window;
  EventHandler *m_eventHandler;
  ImGuiIO m_io;
  float m_spinMultiplier;
  float m_orbitMultiplier;
  bool m_reverseSpinDirection;
  bool m_reverseOrbitDirection;
  bool m_toggleOrbit;
  bool m_toggleSpin;
};

#endif // __MENU_H__
