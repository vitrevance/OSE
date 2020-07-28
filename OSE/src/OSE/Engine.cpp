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
		AssetSystem::instance = new AssetSystem();
		AssetSystem::instance->setAssetDir("C:/Users/N Ashabokov/Desktop/OSE/bin/Debug-x64/Sandbox/assets/");
	}

	void Engine::stop() {
		delete EventSystem::instance;
		delete AssetSystem::instance;
	}

	Window* Engine::createWindow(WindowProps windowProps) {
		this->m_window = new WindowsWindow(windowProps);
		this->m_renderer = new GlRenderer();
		return this->m_window;
	}

	void Engine::disposeWindow() {
		delete this->m_window;
		this->m_window = nullptr;
		delete this->m_renderer;
		this->m_renderer = nullptr;
	}

	void Engine::stopEngine() {
		this->isRunning = false;
	}

	void Engine::setActiveScene(Scene* scene) {
		this->m_activeScene = scene;
		EventSystem::instance->setSceneCallback(std::bind(&Scene::getLayerEventSystem, scene, std::placeholders::_1));
	}

	Scene* Engine::getActiveScene() {
		return this->m_activeScene;
	}

	void Engine::run() {
		while (this->isRunning) {
			if (this->m_window != nullptr) {
				this->m_window->onUpdate();
				this->m_window->onRenderPre();
				this->m_activeScene->render(this->m_renderer);
				this->m_window->onRenderPost();
			}
			TickEvent tickEvent(0);
			EventSystem::instance->postEvent(tickEvent);
		}
	}
}