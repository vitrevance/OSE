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

		template<typename T>
		void postEvent(T& event) {
			std::set<void*>& callbacks = this->m_subscribedEventListeners[T::getStaticEventType()];
			for (void* it : callbacks) {
				std::function<void(T&)> callback = *((onEventWrapper<T>*)it);
				callback(event);
			}

			callbacks = this->m_subscribedEventListeners[EventType::None];
			for (void* it : callbacks) {
				std::function<void(Event&)> callback = *((onEventWrapper<Event>*)it);
				callback(event);
			}
		}

	private:
		std::map<EventType, std::set<void*> > m_subscribedEventListeners;
	};
}

#endif