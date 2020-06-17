#include "Event.h"

namespace OSE {

	Event::Event() {
	}

	Event::~Event() {
	}

	bool Event::isEventInCategory(EventCategory category) {
		return this->getEventCategories() & (int)category;
	}

	bool Event::setCanceled(bool state) {
		if (this->isCancelable()) {
			this->m_isCanceled = state;
			return true;
		}
		return false;
	}
}