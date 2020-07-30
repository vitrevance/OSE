#ifndef OSE_KEYEVENT_H
#define OSE_KEYEVENT_H

#include "Event.h"

namespace OSE {

	class OSE_API KeyEvent : public Event {
	public:
		int getKeyCode();
	protected:
		int m_keyCode;

		KeyEvent(int keyCode);
		~KeyEvent();

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryKey)
	};

	class OSE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount);
		~KeyPressedEvent();

		int getRepeatCount();
		
		EVENT_CLASS_TYPE(EventType::KeyPressed)

	protected:
		int m_repeatCount;
	};

	class OSE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode);
		~KeyReleasedEvent();

		EVENT_CLASS_TYPE(EventType::KeyReleased)
	};
}
#endif