#ifndef OSE_ENGINE_H
#define OSE_ENGINE_H

#include <OSE/Core.h>
#include <OSE/Systems/EventSystem.h>
#include <OSE/Window.h>
#include <OSE/Platforms/WindowsWindow.h>
#include <OSE/Blueprints/Scene.h>
#include <OSE/Blueprints/Actor.h>
#include <OSE/Systems/Renderer.h>

namespace OSE {

	class OSE_API Engine {
	public:
		static Engine* instance;
		

		Engine();
		virtual ~Engine();

		void run();
		void stopEngine();
		void setActiveScene(Scene* scene);
		Scene* getActiveScene();

	protected:
		Window* m_window;
		Scene* m_activeScene;
		Renderer* m_renderer;

		virtual Window* createWindow(WindowProps windowProps = Window::getDefaultWindowProps());
		virtual void disposeWindow();

	private:
		bool isRunning = true;

		void init();
		void stop();
	};
}

#endif