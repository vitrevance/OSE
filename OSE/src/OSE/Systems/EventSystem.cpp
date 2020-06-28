#include "EventSystem.h"

namespace OSE {

	EventSystem* EventSystem::instance = nullptr;

	EventSystem::EventSystem() {
	}


	EventSystem::~EventSystem() {
	}
	
	void EventSystem::subscribeEventListener(EventListenerBase* eventListener) {
		std::vector<EventListenerBase*>& listeners = this->eventListeners[eventListener->getEventType()];
		listeners.push_back(eventListener);
	}

	void EventSystem::postEvent(Event& event) {
		if (this->eventListeners.count(event.getEventType())) {
			std::vector<EventListenerBase*>& listeners = this->eventListeners[event.getEventType()];
			for (EventListenerBase* listener : listeners) {
				listener->onBaseEvent(event);
			}
		}
	}
}