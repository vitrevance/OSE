#include <OSE/Platforms/WindowsWindow.hpp>

#include <OSE/Logger.hpp>

#include <GL/glew.h>

#include <gl/GL.h>

#include <GLFW/glfw3.h>

namespace OSE {

void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods);
void WindowCloseCallback(GLFWwindow* window);
void WindowSizeCallback(GLFWwindow* window, int width, int height);
void WindowMovedCallback(GLFWwindow* window, int x, int y);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int WindowsWindow::isWindowInit = 0;

WindowsWindow::WindowsWindow(WindowProps windowProps) {
  this->m_windowProps = windowProps;
  this->init();
}

WindowsWindow::~WindowsWindow() {
  this->dispose();
}

void WindowsWindow::setVSync(bool state) {
}

void WindowsWindow::onUpdate() {
  glfwPollEvents();
}

void WindowsWindow::onRenderPre() {
  glClearColor(0.02, 0.02, 0.02, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowsWindow::onRenderPost() {
  glfwSwapBuffers(this->m_glfwWindow);
}

void WindowsWindow::init() {
  if (WindowsWindow::isWindowInit <= 0) {
    if (glfwInit() != 0) {
      OSE_LOG(LOG_OSE_INFO, "GLFW initialized");
    } else {
      OSE_LOG(LOG_OSE_ERROR, "GLFW initialization failed");
    }
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  WindowsWindow::isWindowInit++;
  this->m_glfwWindow = glfwCreateWindow(
      this->m_windowProps.width, this->m_windowProps.height,
      this->m_windowProps.title.c_str(),
      this->m_windowProps.isFullscreen ? glfwGetPrimaryMonitor() : nullptr,
      nullptr);
  if (this->m_glfwWindow == nullptr) {
    OSE_LOG(LOG_OSE_ERROR, "GLFW window creation failed");
  }
  glfwMakeContextCurrent(this->m_glfwWindow);
  glewExperimental = GL_TRUE;
  if (glewInit() == GLEW_OK) {
    OSE_LOG(LOG_OSE_INFO, "GLEW initialized");
  } else {
    OSE_LOG(LOG_OSE_ERROR, "GLEW initialization failed");
  }
  glfwSetInputMode(this->m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetKeyCallback(this->m_glfwWindow, KeyCallback);
  glfwSetWindowCloseCallback(this->m_glfwWindow, WindowCloseCallback);
  glfwSetWindowSizeCallback(this->m_glfwWindow, WindowSizeCallback);
  glfwSetWindowPosCallback(this->m_glfwWindow, WindowMovedCallback);
  glfwSetCursorPosCallback(this->m_glfwWindow, MouseCallback);
  glfwSetMouseButtonCallback(this->m_glfwWindow, MouseButtonCallback);
}

void WindowsWindow::dispose() {
  WindowsWindow::isWindowInit--;
  glfwDestroyWindow(this->m_glfwWindow);
  if (WindowsWindow::isWindowInit <= 0) {
    glfwTerminate();
  }
}

void WindowsWindow::grabMouse() {
  glfwSetInputMode(this->m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowsWindow::releaseMouse() {
  glfwSetInputMode(this->m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods) {
  if (action == GLFW_PRESS) {
    KeyPressedEvent event(key, 0);
    EventSystem::instance->postEvent(event);
  }
  if (action == GLFW_REPEAT) {
    KeyPressedEvent event(key, 1);
    EventSystem::instance->postEvent(event);
  }
  if (action == GLFW_RELEASE) {
    KeyReleasedEvent event(key);
    EventSystem::instance->postEvent(event);
  }
}

void WindowCloseCallback(GLFWwindow* window) {
  WindowClosedEvent event;
  EventSystem::instance->postEvent(event);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height) {
  WindowResizedEvent event(width, height);
  EventSystem::instance->postEvent(event);
}

void WindowMovedCallback(GLFWwindow* window, int x, int y) {
  WindowMovedEvent event(x, y);
  EventSystem::instance->postEvent(event);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
  if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width / 2, height / 2);
    MouseMovedEvent event(xpos - width / 2, ypos - height / 2);
    EventSystem::instance->postEvent(event);
  }
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    MouseButtonPressedEvent event(button);
    EventSystem::instance->postEvent(event);
  } else if (action == GLFW_RELEASE) {
    MouseButtonReleasedEvent event(button);
    EventSystem::instance->postEvent(event);
  }
}
}  // namespace OSE