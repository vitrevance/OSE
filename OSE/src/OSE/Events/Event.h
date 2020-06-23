#ifndef OSE_EVENT_H
#define OSE_EVENT_H

#include <OSE/Core.h>


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

		virtual EventType getEventType() const = 0;
		virtual int getEventCategories() const = 0;
		virtual bool isEventInCategory(EventCategory category);

		inline bool isHandled() { return this->m_isHandled; }
		inline bool isCanceled() { return this->m_isCanceled; }
		inline bool isCancelable() { return this->m_isCancelable; }

		bool setCanceled(bool state);

		Event();
		~Event();
	protected:
		bool m_isHandled = false;
		bool m_isCanceled = false;
		bool m_isCancelable = false;
	};

#define EVENT_CLASS_TYPE(type) virtual EventType getEventType() const override { return type; } static EventType getStaticEventType() { return type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getEventCategories() const override { return category; }
}

#endif