#include "Engine.h"

namespace OSE {

	Engine::Engine() {
		(new Logger())->Start();
		this->init();
	}

	Engine::~Engine() {
		Logger::instance->Stop();
	}

	void Engine::init() {
		OSE_LOG(LOG_OSE_TRACE, "Engine initialization...");

	}

	void Engine::run() {
		
	}

	
}