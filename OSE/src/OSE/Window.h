#ifndef OSE_WINDOW_H
#define OSE_WINDOW_H

#include <OSE/Core.h>
#include <OSE/Systems/EventSystem.h>

namespace OSE {

	struct WindowProps {
		string title;
		int width, height;
		bool isVSYNC;
	};

	class Window {
	public:
		virtual WindowProps getDefaultWindowParams() {
			return WindowProps{ "OSE App", 1280, 720, false };
		}

		virtual int getWidth() {
			return this->m_windowProps.width;
		}

		virtual int getHeight() {
			return this->m_windowProps.height;
		}

		virtual bool isVSync() {
			return this->m_windowProps.isVSYNC;
		}

		virtual void setVSync(bool state) = 0;
		virtual void onUpdate() = 0;
	protected:
		Window() {}
		~Window() {}

		WindowProps m_windowProps;
	};
}
#endif