#ifndef OSE_WINDOW_H
#define OSE_WINDOW_H

#include <OSE/Core.h>
#include <OSE/Systems/EventSystem.h>

namespace OSE {

	struct WindowProps {
		string title;
		int width, height;
		bool isVSYNC;
		bool isFullscreen;
	};

	class OSE_API Window {
	public:
		virtual ~Window() {};

		static WindowProps getDefaultWindowProps() {
			return WindowProps{ "OSE App", 1280, 720, false, false };
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

		virtual bool isFullscreen() {
			return this->m_windowProps.isFullscreen;
		}

		virtual void setVSync(bool state) = 0;
		virtual void onUpdate() = 0;
		virtual void onRenderPre() = 0;
		virtual void onRenderPost() = 0;

		WindowProps m_windowProps;
	protected:
		Window() {};
	};
}
#endif