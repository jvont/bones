#pragma once

#include <core/input/gamepad.h>
#include <core/input/keyboard.h>
#include <core/input/mouse.h>
#include <core/math/spatial/point2.h>
#include <core/math/spatial/rect.h>
#include <core/typedefs.h>

#include <variant>

namespace bones
{
#pragma region "Event structures"
  struct CoreEvent
  {

  };

  struct WindowEvent
  {
    Rect bounds;
  };

  struct KeyEvent
  {
    Key key;
    KeyMod mod;
    bool pressed;
    bool repeat;
  };

  struct MouseButtonEvent
  {
    MouseButton button;
    Point2 pos;
    bool pressed;
    u8 clicks;
  };

  struct MouseScrollEvent
  {
    int amount;
  };

  struct MouseMotionEvent
  {
    MouseButton button;
    Point2 pos;
    Point2 delta;
  };

  struct GamepadButtonEvent
  {
    GamepadButton button;
    bool pressed;
    bool repeat;
  };

  struct GamepadAxisEvent
  {
    GamepadAxis axis;
    Point2 amount;
  };

#pragma endregion
#pragma region "InputEvent variant"
  using InputEvent = std::variant<
    KeyEvent,

    MouseButtonEvent,
    MouseScrollEvent,
    MouseMotionEvent,

    GamepadButtonEvent,
    GamepadAxisEvent
  >;

  template<class T>
  bool event_is(const InputEvent& event);

  template<> inline bool event_is<KeyEvent>(const InputEvent& event) { return event.index() == 0; }
  template<> inline bool event_is<MouseButtonEvent>(const InputEvent& event) { return event.index() == 1; }
  template<> inline bool event_is<MouseScrollEvent>(const InputEvent& event) { return event.index() == 2; }
  template<> inline bool event_is<MouseMotionEvent>(const InputEvent& event) { return event.index() == 3; }
  template<> inline bool event_is<GamepadButtonEvent>(const InputEvent& event) { return event.index() == 4; }
  template<> inline bool event_is<GamepadAxisEvent>(const InputEvent& event) { return event.index() == 5; }

  template<class T>
  T event_cast(InputEvent& event)
  {
    return std::get<T>(event);
  }

  template<class T>
  const T event_cast(const InputEvent& event)
  {
    return std::get<T>(event);
  }

  template<class T>
  T* event_cast_if(InputEvent& event)
  {
    return std::get_if<T>(&event);
  }

  template<class T>
  const T* event_cast_if(const InputEvent& event)
  {
    return std::get_if<T>(&event);
  }

#pragma endregion
#pragma region "Event variant (..., InputEvent)"
  using Event = std::variant<
    CoreEvent,
    WindowEvent,
    InputEvent
  >;

  template<class T>
  bool event_is(const Event& event);

  template<> inline bool event_is<CoreEvent>(const Event& event) { return event.index() == 0; }
  template<> inline bool event_is<WindowEvent>(const Event& event) { return event.index() == 1; }
  template<> inline bool event_is<InputEvent>(const Event& event) { return event.index() == 2; }

  template<class T>
  T event_cast(Event& event)
  {
    return std::get<T>(event);
  }

  template<class T>
  const T event_cast(const Event& event)
  {
    return std::get<T>(event);
  }

  template<class T>
  T* event_cast_if(Event& event)
  {
    return std::get_if<T>(&event);
  }

  template<class T>
  const T* event_cast_if(const Event& event)
  {
    return std::get_if<T>(&event);
  }

#pragma endregion
}