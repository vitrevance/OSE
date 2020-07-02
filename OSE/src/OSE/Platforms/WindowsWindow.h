#ifndef OSE_WINDOWSWINDOW_H
#define OSE_WINDOWSWINDOW_H

#include <OSE/Window.h>
//#include <GLFW/glfw3.h>

namespace OSE {

	class OSE_API WindowsWindow : public Window {
	public:
		WindowsWindow();
		~WindowsWindow();

		void onUpdate() override;
	protected:
		void init();
		void dispose();
	};
}

#endif