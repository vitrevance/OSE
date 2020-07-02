#ifndef OSE_EVENTSYSTEM_H
#define OSE_EVENTSYSTEM_H

#include <OSE/Events/Event.h>

namespace OSE {

	class OSE_API EventListenerBase {
	public:
		virtual EventType getEventType() = 0;
		virtual bool onBaseEvent(Event&  event) = 0;
	protected:
		EventListenerBase() {}
		~EventListenerBase() {}
	};

	class OSE_API EventSystem {
	public:

		static EventSystem* instance;

		EventSystem();
		~EventSystem();

		void subscribeEventListener(EventListenerBase* eventListener);
		void postEvent(Event& event);

	private:
		std::map<EventType, std::vector<EventListenerBase*> > eventListeners;
	};

	template<typename T>
	class OSE_API EventListener : private EventListenerBase {
		static_assert(std::is_base_of<Event, T>::value, "T must inherit from Event");
	public:

		EventListener() {
			EventSystem::instance->subscribeEventListener(this);
		}

		~EventListener() {
		}

		virtual bool onEvent(T& event) = 0;

		EventType getEventType() override {
			return T::getStaticEventType();
		}

	private:
		bool onBaseEvent(Event& event) override {
			return this->onEvent((T&)event);
		}
	};
}

#endif