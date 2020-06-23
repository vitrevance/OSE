#ifndef OSE_MOUSEEVENT_H
#define OSE_MOUSEEVENT_H

#include "Event.h"

namespace OSE {

	class OSE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y);
		~MouseMovedEvent();

		float getX();
		float getY();

		EVENT_CLASS_TYPE(EventType::MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)

	protected:
		float m_mouseX, m_mouseY;
	};

	class OSE_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset);
		~MouseScrolledEvent();

		float getXOffset();
		float getYOffset();

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)
		EVENT_CLASS_TYPE(EventType::MouseScrolled);
	protected:
		float m_xOffset, m_yOffset;
	};

	class OSE_API MouseButtonEvent : public Event {
	public:
		int getButton();

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse | EventCategory::CategoryMouseButton);
	protected:
		MouseButtonEvent(int button);
		~MouseButtonEvent();

		int m_button;
	};

	class OSE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button);
		~MouseButtonPressedEvent();

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
	};

	class OSE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button);
		~MouseButtonReleasedEvent();

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
	};
}
#endif