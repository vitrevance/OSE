#include "EventSystem.h"

namespace OSE {

	EventSystem::EventSystem() {
	}


	EventSystem::~EventSystem() {
	}
	
	void EventSystem::subscribeEventListener(EventListenerBase* eventListener) {
		this->eventListeners.push_back(eventListener);
	}

	void EventSystem::postEvent(Event& event) {
		for (EventListenerBase* listener : this->eventListeners) {
			if (listener->getEventType() == event.getEventType()) {
				listener->onEvent(event);
			}
		}
	}
}