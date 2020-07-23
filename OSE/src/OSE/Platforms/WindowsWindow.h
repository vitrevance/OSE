#ifndef OSE_WINDOWSWINDOW_H
#define OSE_WINDOWSWINDOW_H

#include <GLFW/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <OSE/Window.h>
#include <OSE/Events/WindowEvent.h>
#include <OSE/Events/KeyEvent.h>
#include <OSE/Events/MouseEvent.h>

namespace OSE {

	class OSE_API WindowsWindow : public Window {
	public:
		WindowsWindow(WindowProps windowProps);
		virtual ~WindowsWindow() override;

		void onUpdate() override;
		void onRenderPre() override;
		void onRenderPost() override;
		void setVSync(bool state) override;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void window_close_callback(GLFWwindow* window);
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void window_moved_callback(GLFWwindow* window, int x, int y);

	protected:
		static int s_isWindowInit;
		GLFWwindow* m_glfwWindow;

		void init();
		void dispose();
	};
}

#endif