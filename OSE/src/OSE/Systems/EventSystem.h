#ifndef OSE_EVENTSYSTEM_H
#define OSE_EVENTSYSTEM_H

#include <OSE/Events/Event.h>
#include <vector>

namespace OSE {

	class OSE_API EventListenerBase {
	public:
		virtual EventType getEventType() = 0;
		virtual bool onEvent(Event& event) = 0;
	protected:
		EventListenerBase() {};
	};

	class OSE_API EventSystem {
	public:
		EventSystem();
		~EventSystem();

		void subscribeEventListener(EventListenerBase* eventListener);
		void postEvent(Event& event);

	private:
		std::vector<EventListenerBase*> eventListeners;
	};
}

#endif

#ifndef OSE_EVENTLISTENER_H
#define OSE_EVENTLISTENER_H

#include <OSE/Engine.h>

namespace OSE {

	template<typename T>
	class OSE_API EventListener : public EventListenerBase {
		static_assert(std::is_base_of<Event, T>::value, "T must inherit from Event");
	public:

		EventListener() {
			Engine::instance->getEventSystem()->subscribeEventListener(this);
		}

		~EventListener() {
		}

		bool onEvent(Event& event) override {
			return this->onEvent((T&)event);
		}

		virtual bool onEvent(T& event) = 0;

		EventType getEventType() override {
			return T::getStaticEventType();
		}
	};
}

#endif