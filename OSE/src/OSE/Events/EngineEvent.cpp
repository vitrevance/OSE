#include "EngineEvent.h"

namespace OSE {

	TickEvent::TickEvent(float deltaTime) : m_deltaTime(deltaTime) {
	}

	TickEvent::~TickEvent() {
	}

	float TickEvent::getDeltaTime() {
		return this->m_deltaTime;
	}
}