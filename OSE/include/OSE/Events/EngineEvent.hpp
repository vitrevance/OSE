#ifndef OSE_ENGINEEVENT_H
#define OSE_ENGINEEVENT_H

#include <OSE/Events/Event.hpp>

namespace OSE {

class OSE_API TickEvent : public Event {
 public:
  TickEvent(float deltaTime);
  ~TickEvent();

  float getDeltaTime();

  EVENT_CLASS_CATEGORY(EventCategory::CategoryApp)
  EVENT_CLASS_TYPE(EventType::Tick)

 protected:
  float m_deltaTime;
};
}  // namespace OSE

#endif