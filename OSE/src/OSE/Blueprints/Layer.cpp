#include "Layer.h"

namespace OSE {
	Layer::Layer() {
	}

	Layer::~Layer() {
	}

	void Layer::add(Entity* entity) {
		this->m_entities.insert(entity);
	}

	void Layer::remove(Entity* entity) {
		this->m_entities.erase(entity);
		if (dynamic_cast<EventListenerBase*>(entity)) {
			this->unsubscribeEventListener((EventListenerBase*)entity);
		}
	}

	void Layer::subscribeEventListener(EventListenerBase* eventListener) {
		this->m_eventSystem.subscribeEventListener(eventListener);
	}

	void Layer::unsubscribeEventListener(EventListenerBase* eventListener) {
		this->m_eventSystem.unsubscribeEventListener(eventListener);
	}

	void Layer::addAndSubscribe(Entity* entity) {
		this->add(entity);
		this->subscribeEventListener(entity);
	}

	void Layer::clear() {
		for (Entity* entity : this->m_entities) {
			delete entity;
		}
		this->m_entities.clear();
		this->m_eventSystem = EventSystem();
	}

	void Layer::free() {
		this->m_entities.clear();
		this->m_eventSystem = EventSystem();
	}

	EventSystem& Layer::eventSystem() {
		return this->m_eventSystem;
	}
}