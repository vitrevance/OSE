#include <OSE/Events/KeyEvent.hpp>

namespace OSE {

KeyEvent::KeyEvent(int keyCode) {
  this->m_keyCode = keyCode;
}

KeyEvent::~KeyEvent() {
}

int KeyEvent::getKeyCode() {
  return this->m_keyCode;
}

KeyPressedEvent::KeyPressedEvent(int keyCode, int repeatCount)
    : KeyEvent(keyCode),
      m_repeatCount(repeatCount) {
}

KeyPressedEvent::~KeyPressedEvent() {
}

int KeyPressedEvent::getRepeatCount() {
  return this->m_repeatCount;
}

KeyReleasedEvent::KeyReleasedEvent(int keyCode)
    : KeyEvent(keyCode) {
}

KeyReleasedEvent::~KeyReleasedEvent() {
}
}  // namespace OSE