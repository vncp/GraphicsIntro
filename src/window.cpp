#include <window.h>

Window::Window(EventHandler *eventHandler, Args *args)
  : ArgWrapper(args),
  gWindow(nullptr),
  m_menu(nullptr),
  m_eventHandler(eventHandler)
{
}

Window::~Window()
{
  glfwTerminate();
  delete m_menu;
  m_menu = NULL;
  gWindow = NULL;
}

bool Window::Initialize(const char *name, int* width, int* height)
{
  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW failed to initialize.");
    glfwTerminate();
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_RED_BITS, 5);
  glfwWindowHint(GLFW_BLUE_BITS, 5);
  glfwWindowHint(GLFW_GREEN_BITS, 5);

  gWindow =  glfwCreateWindow(640, 480, name, NULL, NULL);
  if (!gWindow) {
    fprintf(stderr, "GLFW window failed to initialize.");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(gWindow);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "GLEW failed to initialize. (%s).", glewGetErrorString(err));
    glfwTerminate();
  }

  glfwSwapInterval(1);

  m_menu = new Menu(gWindow, m_eventHandler);

  return true;
}

GLFWwindow *Window::getWindow() {
  return gWindow;
}

void Window::Swap()
{
  glfwSwapBuffers(gWindow);
}

void Window::RenderMenu()
{
  m_menu->refresh();
}

void Window::RenderMenuDrawData()
{
  m_menu->renderDrawData();
}

bool Window::isMenuHovered()
{
  return m_menu->m_menuHovered;
}
