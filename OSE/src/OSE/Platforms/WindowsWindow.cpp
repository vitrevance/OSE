#include "WindowsWindow.h"

namespace OSE {

	int WindowsWindow::s_isWindowInit = 0;

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
		if (WindowsWindow::s_isWindowInit <= 0) {
			if (glfwInit()) {
				OSE_LOG(LOG_OSE_INFO, "GLFW initialized")
			}
			else {
				OSE_LOG(LOG_OSE_ERROR, "GLFW initialization failed")
			}
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		WindowsWindow::s_isWindowInit++;
		this->m_glfwWindow = glfwCreateWindow(this->m_windowProps.width, this->m_windowProps.height, this->m_windowProps.title.c_str(),
			this->m_windowProps.isFullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
		if (!this->m_glfwWindow) {
			OSE_LOG(LOG_OSE_ERROR, "GLFW window creation failed")
		}
		glfwMakeContextCurrent(this->m_glfwWindow);
		glewExperimental = GL_TRUE;
		if (glewInit() == GLEW_OK) {
			OSE_LOG(LOG_OSE_INFO, "GLEW initialized")
		}
		else {
			OSE_LOG(LOG_OSE_ERROR, "GLEW initialization failed")
		}
		glfwSetKeyCallback(this->m_glfwWindow, key_callback);
		glfwSetWindowCloseCallback(this->m_glfwWindow, window_close_callback);
		glfwSetWindowSizeCallback(this->m_glfwWindow, window_size_callback);
		glfwSetWindowPosCallback(this->m_glfwWindow, window_moved_callback);
	}

	void WindowsWindow::dispose() {
		WindowsWindow::s_isWindowInit--;
		glfwDestroyWindow(this->m_glfwWindow);
		if (WindowsWindow::s_isWindowInit <= 0) {
			glfwTerminate();
		}
	}

	void WindowsWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

	void WindowsWindow::window_close_callback(GLFWwindow* window) {
		WindowClosedEvent event;
		EventSystem::instance->postEvent(event);
	}

	void WindowsWindow::window_size_callback(GLFWwindow* window, int width, int height) {
		WindowResizedEvent event(width, height);
		EventSystem::instance->postEvent(event);
	}

	void WindowsWindow::window_moved_callback(GLFWwindow* window, int x, int y) {
		WindowMovedEvent event(x, y);
		EventSystem::instance->postEvent(event);
	}
}