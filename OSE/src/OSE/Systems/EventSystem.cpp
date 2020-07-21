#include "EventSystem.h"

namespace OSE {

	EventSystem* EventSystem::instance = nullptr;

	EventSystem::EventSystem() {
	}


	EventSystem::~EventSystem() {
	}
	
	void EventSystem::subscribeEventListener(EventListenerBase* eventListener) {
		std::map<EventType, void*>& callbacks = eventListener->getEventType();
		std::map<EventType, void*>::iterator it;
		it = callbacks.begin();
		for (it = callbacks.begin(); it != callbacks.end(); it++) {
			this->m_subscribedEventListeners[it->first].insert(it->second);
		}
	}

	void EventSystem::unsubscribeEventListener(EventListenerBase* eventListener) {
		std::map<EventType, void*>& callbacks = eventListener->getEventType();
		std::map<EventType, void*>::iterator it;
		it = callbacks.begin();
		for (it = callbacks.begin(); it != callbacks.end(); it++) {
			this->m_subscribedEventListeners[it->first].erase(it->second);
		}
	}

	void EventSystem::setSceneCallback(std::function<EventSystem*(int)> callback) {
		this->m_sceneLayerCallback = callback;
	}
}