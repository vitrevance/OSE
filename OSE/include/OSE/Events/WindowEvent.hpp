#ifndef OSE_WINDOWEVENT_H
#define OSE_WINDOWEVENT_H

#include <OSE/Events/Event.hpp>

namespace OSE {

class OSE_API WindowResizedEvent : public Event {
 public:
  WindowResizedEvent(int width, int height);
  ~WindowResizedEvent();

  int getWidth();
  int getHeight();

  EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
  EVENT_CLASS_TYPE(EventType::WindowResized)

 protected:
  int m_width, m_height;
};

class OSE_API WindowMovedEvent : public Event {
 public:
  WindowMovedEvent(int x, int y);
  ~WindowMovedEvent();

  int getX();
  int getY();

  EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
  EVENT_CLASS_TYPE(EventType::WindowMoved)

 protected:
  int m_x, m_y;
};

class OSE_API WindowClosedEvent : public Event {
 public:
  WindowClosedEvent();
  ~WindowClosedEvent();

  EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
  EVENT_CLASS_TYPE(EventType::WindowClosed)
};

class OSE_API WindowLostFocusEvent : public Event {
 public:
  WindowLostFocusEvent();
  ~WindowLostFocusEvent();

  EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
  EVENT_CLASS_TYPE(EventType::WindowLostFocus)
};
}  // namespace OSE

#endif