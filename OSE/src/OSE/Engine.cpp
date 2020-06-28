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
		EventSystem::instance = new EventSystem();
	}

	void Engine::stop() {
		delete EventSystem::instance;
	}

	void Engine::run() {
		
	}
}