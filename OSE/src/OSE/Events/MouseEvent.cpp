#include "MouseEvent.h"

namespace OSE {
	MouseMovedEvent::MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {
	}

	MouseMovedEvent::~MouseMovedEvent() {
	}

	float MouseMovedEvent::getX() {
		return this->m_mouseX;
	}

	float MouseMovedEvent::getY() {
		return this->m_mouseY;
	}

	MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {
	}

	MouseButtonEvent::MouseButtonEvent(int button) : m_button(button) {
	}

	MouseButtonEvent::~MouseButtonEvent() {
	}

	int MouseButtonEvent::getButton() {
		return this->m_button;
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
	}

	MouseButtonPressedEvent::~MouseButtonPressedEvent() {
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
	}

	MouseButtonReleasedEvent::~MouseButtonReleasedEvent() {
	}
}