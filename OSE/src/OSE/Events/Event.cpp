#include <OSE/Events/Event.hpp>

namespace OSE {

Event::Event() {
}

Event::~Event() {
}

bool Event::isEventInCategory(EventCategory category) {
  return (this->getEventCategories() & (int)category) != 0;
}

bool Event::setCanceled(bool state) {
  if (this->isCancelable()) {
    this->m_isCanceled = state;
    return true;
  }
  return false;
}

void Event::setHandled() {
  this->m_isHandled = true;
}
}  // namespace OSE