#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>
#include "window.h"
#include "graphics.h"
#include "menu.h"
#include "graphics_headers.h"
#include "argwrapper.h"

class Engine : public ArgWrapper
{
  public:
    Engine(const char *name, int width, int height, Args *args = nullptr);
    Engine(const char *name, Args *args = nullptr);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    unsigned int getDT();
    long long GetCurrentTimeMillis();

  private:
    // Window related variables
    EventHandler *m_eventHandler;
    Window *m_window;
    const char *m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
};

#endif // ENGINE_H
