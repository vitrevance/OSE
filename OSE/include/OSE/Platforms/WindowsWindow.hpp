#ifndef OSE_WINDOWSWINDOW_H
#define OSE_WINDOWSWINDOW_H

#include <OSE/Window.hpp>
#include <OSE/Events/WindowEvent.hpp>
#include <OSE/Events/KeyEvent.hpp>
#include <OSE/Events/MouseEvent.hpp>

struct GLFWwindow;

namespace OSE {

class OSE_API WindowsWindow : public Window {
 public:
  WindowsWindow(WindowProps windowProps);
  virtual ~WindowsWindow() override;

  void onUpdate() override;
  void onRenderPre() override;
  void onRenderPost() override;
  void setVSync(bool state) override;
  void grabMouse() override;
  void releaseMouse() override;

 protected:
  static int s_isWindowInit;
  GLFWwindow* m_glfwWindow;

  void init();
  void dispose();
};
}  // namespace OSE

#endif