#include "Engine.h"

namespace OSE {

	Engine* Engine::instance;

	Engine::Engine() {
		(new Logger())->Start();
		Engine::instance = this;
		this->init();
	}

	Engine::~Engine() {
		this->stop();
		Logger::instance->Stop();
	}

	void Engine::init() {
		OSE_LOG(LOG_OSE_TRACE, "Engine initialization...");
		this->m_window = nullptr;
		this->m_activeScene = nullptr;
		EventSystem::instance = new EventSystem();
		//EventSystem::instance->setStaticCallback(&Engine::onEvent);
	}

	void Engine::stop() {
		delete EventSystem::instance;
	}

	Window* Engine::createWindow(WindowProps windowProps) {
		this->m_window = new WindowsWindow(windowProps);
		return this->m_window;
	}

	void Engine::disposeWindow() {
		delete this->m_window;
		this->m_window = nullptr;
	}

	void Engine::stopEngine() {
		this->isRunning = false;
	}

	void Engine::setActiveScene(Scene* scene) {
		this->m_activeScene = scene;
	}

	Scene* Engine::getActiveScene() {
		return this->m_activeScene;
	}

	void Engine::run() {
		while (this->isRunning) {
			if (this->m_window != nullptr) {
				this->m_window->onUpdate();
			}
			TickEvent tickEvent();
			EventSystem::instance->postEvent(tickEvent);
		}
	}
}