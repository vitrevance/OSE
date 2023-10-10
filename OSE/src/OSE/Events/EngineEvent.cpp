#include <OSE/Events/EngineEvent.hpp>

namespace OSE {

TickEvent::TickEvent(float deltaTime)
    : m_deltaTime(deltaTime) {
}

TickEvent::~TickEvent() {
}

float TickEvent::getDeltaTime() {
  return this->m_deltaTime;
}
}  // namespace OSE