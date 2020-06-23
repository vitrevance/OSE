#include "WindowEvent.h"

namespace OSE {

	WindowResizedEvent::WindowResizedEvent(int width, int height) : m_width(width), m_height(height) {
	}

	WindowResizedEvent::~WindowResizedEvent() {
	}

	int WindowResizedEvent::getWidth() {
		return this->m_width;
	}

	int WindowResizedEvent::getHeight() {
		return this->m_height;
	}

	WindowMovedEvent::WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {
	}

	WindowMovedEvent::~WindowMovedEvent() {
	}

	int WindowMovedEvent::getX() {
		return this->m_x;
	}

	int WindowMovedEvent::getY() {
		return this->m_y;
	}

	WindowClosedEvent::WindowClosedEvent() {
	}

	WindowClosedEvent::~WindowClosedEvent() {
	}

	WindowLostFocusEvent::WindowLostFocusEvent() {
	}

	WindowLostFocusEvent::~WindowLostFocusEvent() {
	}
}