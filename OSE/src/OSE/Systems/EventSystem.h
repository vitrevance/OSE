#ifndef OSE_EVENTSYSTEM_H
#define OSE_EVENTSYSTEM_H

#include <OSE/Events/Event.h>

namespace OSE {

	class OSE_API EventSystem {
	public:

		static EventSystem* instance;

		EventSystem();
		~EventSystem();

		void subscribeEventListener(EventListenerBase* eventListener);
		void unsubscribeEventListener(EventListenerBase* eventListener);

		void setSceneCallback(std::function<EventSystem*(int)> callback);

		template<typename T>
		void postEvent(T& event) {
			if (this->m_subscribedEventListeners.count(T::getStaticEventType())) {
				std::set<void*>& callbacks = this->m_subscribedEventListeners[T::getStaticEventType()];
				for (void* it : callbacks) {
					std::function<void(T&)> callback = *((onEventWrapper<T>*)it);
					callback(event);
				}
			}

			if (this->m_subscribedEventListeners.count(EventType::None)) {
				std::set<void*>& callbacks = this->m_subscribedEventListeners[EventType::None];
				for (void* it : callbacks) {
					std::function<void(Event&)> callback = *((onEventWrapper<Event>*)it);
					callback(event);
				}
			}

			if (this->m_sceneLayerCallback) {
				int i = 0;
				EventSystem* layerEventSystem = this->m_sceneLayerCallback(i);
				while (layerEventSystem != nullptr) {
					layerEventSystem->postEvent(event);
					i++;
					layerEventSystem = this->m_sceneLayerCallback(i);
				}
			}
		}

	private:
		std::map<EventType, std::set<void*> > m_subscribedEventListeners;
		std::function<EventSystem*(int)> m_sceneLayerCallback;
	};
}

#endif