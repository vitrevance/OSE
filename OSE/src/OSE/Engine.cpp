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
		this->eventSystem = new EventSystem();
	}

	void Engine::stop() {
		delete this->eventSystem;
	}

	void Engine::run() {
		
	}
}