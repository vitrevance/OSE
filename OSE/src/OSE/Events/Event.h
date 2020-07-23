#ifndef OSE_EVENT_H
#define OSE_EVENT_H

#include <OSE/Core.h>
#include <functional>

namespace OSE {

	enum class EventType {
		None = 0,
		WindowClosed, WindowResized, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		Tick,
		EVENTTYPE_ITEMS
	};

	enum EventCategory {
		None                = 0,
		CategoryApp         = BIT(0),
		CategoryWindow      = BIT(1),
		CategoryInput       = BIT(2),
		CategoryKey         = BIT(3),
		CategoryMouse       = BIT(4),
		CategoryMouseButton = BIT(5)
	};

	class OSE_API Event {
	public:
		static EventType getStaticEventType() { return EventType::None; }

		virtual EventType getEventType() const = 0;
		virtual int getEventCategories() const = 0;
		virtual bool isEventInCategory(EventCategory category);

		inline bool isHandled() { return this->m_isHandled; }
		inline bool isCanceled() { return this->m_isCanceled; }
		inline bool isCancelable() { return this->m_isCancelable; }

		bool setCanceled(bool state);
		void setHandled();

		Event();
		~Event();
	protected:
		bool m_isHandled = false;
		bool m_isCanceled = false;
		bool m_isCancelable = false;
	};

#define EVENT_CLASS_TYPE(type) virtual EventType getEventType() const override { return type; } static EventType getStaticEventType() { return type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getEventCategories() const override { return category; }

	template<typename T>
	struct onEventWrapper {
		std::function<void(T&)> m_fun;
		onEventWrapper(std::function<void(T&)> fun) {
			this->m_fun = fun;
		}
		operator std::function<void(T&)>() const { return m_fun; }
	};

	class OSE_API EventListenerBase {
	public:
		std::map<EventType, void*>& getEventType() {
			return this->m_eventTypes;
		}

	protected:
		std::map<EventType, void* > m_eventTypes;

		EventListenerBase() {}
		~EventListenerBase() {}
	};

	template<typename T>
	class EventListener : virtual public EventListenerBase {
	public:
		EventListener() {
			static_assert(std::is_base_of<Event, T>::value, "T must inherit from Event");
			std::function<void(T&)> callback = std::bind(&EventListener<T>::onEvent, this, std::placeholders::_1);
			onEventWrapper<T>* fun = new onEventWrapper<T>(callback);
			this->m_eventTypes[T::getStaticEventType()] = (void*)fun;
		}

		virtual ~EventListener() {
			delete (onEventWrapper<T>*)this->m_eventTypes[T::getStaticEventType()];
			this->m_eventTypes.erase(T::getStaticEventType());
		}

		virtual void onEvent(T& event) = 0;
	};
}

#endif