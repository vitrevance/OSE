#ifndef OSE_EVENT_H
#define OSE_EVENT_H

#include"../Core.h"


namespace OSE {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory {
		None                = 0,
		CategoryApp         = BIT(0),
		CategoryWindow      = BIT(1),
		CategoryInput       = BIT(2),
		CategoryKey         = BIT(3),
		CategoryMouse       = BIT(4),
		CategoryMouseButton = BIT(5)
	};

	class OSE_API Event {
	protected:
		bool m_isHandled = false;
		bool m_isCanceled = false;
		bool m_isCancelable = false;

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

	
	};
}

#endif