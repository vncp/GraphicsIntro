#ifndef WINDOW_H
#define WINDOW_H

#include "graphics_headers.h"
#include <string>
#include "argwrapper.h"
#include "imgui.h"
#include "menu.h"
#include "eventhandler.h"

class Window : public ArgWrapper
{
  public:
    Window(EventHandler *eventHandler = nullptr, Args *args = nullptr);
    ~Window();
    bool Initialize(const char *name, int* width, int* height);
    GLFWwindow *getWindow();
    void Swap();
    void RenderMenu();
    void RenderMenuDrawData();
    bool isMenuHovered();

  private:
    GLFWwindow* gWindow;
    Menu *m_menu;
    EventHandler *m_eventHandler;
};

#endif /* WINDOW_H */
