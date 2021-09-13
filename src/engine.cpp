#include "engine.h"
#include "argwrapper.h"
#include <functional>

Engine::Engine(const char *name, int width, int height, Args *args)
  :ArgWrapper(args),
  m_window(nullptr),
  m_WINDOW_NAME(name),
  m_WINDOW_WIDTH(width),
  m_WINDOW_HEIGHT(height),
  m_FULLSCREEN(false)
{
  m_eventHandler = new EventHandler();
}

Engine::Engine(const char *name, Args *args)
  :ArgWrapper(args),
  m_window(nullptr),
  m_WINDOW_NAME(name),
  m_WINDOW_WIDTH(0),
  m_WINDOW_HEIGHT(0),
  m_FULLSCREEN(true)
{
  m_eventHandler = new EventHandler();
}

Engine::~Engine()
{
  delete m_eventHandler;
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_eventHandler);
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }
  glfwSetWindowUserPointer(m_window->getWindow(), this);

  // Start the graphics
  m_graphics = new Graphics(m_eventHandler, m_args);
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // Set up keyboard binds
  glfwSetKeyCallback(m_window->getWindow(), [](GLFWwindow *window,
                                                           int key,
                                                           int scancode,
                                                           int action,
                                                           int mods) {
    Engine *engine = reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window));
    if(!engine) return;
    if (action == GLFW_PRESS) {
      switch (key) {
        case GLFW_KEY_Z:
          engine->m_eventHandler->notify(GLFW_KEY_Z);
          break;
        case GLFW_KEY_X:
          engine->m_eventHandler->notify(GLFW_KEY_X);
          break;
        case GLFW_KEY_A:
          engine->m_eventHandler->notify(GLFW_KEY_A);
          break;
        case GLFW_KEY_S:
          engine->m_eventHandler->notify(GLFW_KEY_S);
          break;
      }
    }
  });

  // Set up mouse bind
  glfwSetMouseButtonCallback(m_window->getWindow(), [](GLFWwindow *window,
                                                                    int button,
                                                                    int action,
                                                                    int mods) {
    Engine *engine = reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window));
    if(!engine) return;
    if (!engine->m_window->isMenuHovered() && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
      engine->m_eventHandler->notify(GLFW_MOUSE_BUTTON_LEFT);
    }
  });

  // No errors
  return true;
}

void Engine::Run()
{
  while(!glfwWindowShouldClose(m_window->getWindow()))
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    glfwPollEvents();

    // Render menu
    m_window->RenderMenu();

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_graphics->Render();

    // Menu render draw data
    m_window->RenderMenuDrawData();

    // Swap to the Window
    m_window->Swap();
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
