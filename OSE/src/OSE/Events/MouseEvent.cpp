#include "MouseEvent.h"

namespace OSE {
	MouseMovedEvent::MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {
	}

	MouseMovedEvent::~MouseMovedEvent() {
	}

	MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {
	}

	MouseButtonEvent::MouseButtonEvent(int button) : m_button(button) {
	}

	int MouseButtonEvent::getButton() {
		return this->m_button;
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
	}
}