#include "KeyEvent.h"

namespace OSE {

	KeyEvent::KeyEvent(int keyCode) {
		this->m_keyCode = keyCode;
	}


	KeyEvent::~KeyEvent() {
	}

	KeyPressedEvent::KeyPressedEvent(int keyCode, int repeatCount)
		: KeyEvent(keyCode), m_repeatCount(repeatCount) {
	}

	KeyPressedEvent::~KeyPressedEvent() {
	}

	int KeyPressedEvent::getRepeatCount() {
		return this->m_repeatCount;
	}

	KeyReleasedEvent::KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {
	}

	KeyReleasedEvent::~KeyReleasedEvent() {
	}
}