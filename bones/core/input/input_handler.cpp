#include <core/input/input_handler.h>

namespace bones
{
  bool InputHandler::pressed(Key key)
  {
    return active_keys.count(key);
  }

  bool InputHandler::released(Key key)
  {
    return (!active_keys.count(key));
  }

  bool InputHandler::pressed(MouseButton button)
  {
    return active_mouse_buttons.count(button);
  }

  bool InputHandler::released(MouseButton button)
  {
    return (!active_mouse_buttons.count(button));
  }

  Point2 InputHandler::get_mouse() const
  {
    return last_mouse_pos;
  }

  bool InputHandler::pressed(GamepadButton button)
  {
    return active_gamepad_buttons.count(button);
  }

  bool InputHandler::released(GamepadButton button)
  {
    return (!active_gamepad_buttons.count(button));
  }

  Point2 InputHandler::get_axis(GamepadAxis axis) const
  {
    std::map<GamepadAxis, Point2>::const_iterator it = last_axis_pos.find(axis);
    if (it != last_axis_pos.end())
      return it->second;
    else
      return Point2();
  }

  // bool InputHandler::pressed(const Str& action)
  // {

  // }

  // bool InputHandler::released(const Str& action)
  // {

  // }

  void InputHandler::handle_event(const Event& event)
  {
    if (const InputEvent* ip = event_cast_if<InputEvent>(event))
    {
      InputEvent i = *ip;

      if (const KeyEvent* e = event_cast_if<KeyEvent>(i))
      {
        if (e->pressed)
          active_keys.insert(e->key);
        else
          active_keys.erase(e->key);
      }
      else if (const MouseButtonEvent* e = event_cast_if<MouseButtonEvent>(i))
      {
        if (e->pressed)
          active_mouse_buttons.insert(e->button);
        else
          active_mouse_buttons.erase(e->button);
      }
      else if (const MouseMotionEvent* e = event_cast_if<MouseMotionEvent>(i))
      {
        last_mouse_pos = e->pos;
      }
      else if (const GamepadButtonEvent* e = event_cast_if<GamepadButtonEvent>(i))
      {
        if (e->pressed)
          active_gamepad_buttons.insert(e->button);
        else
          active_gamepad_buttons.erase(e->button);
      }
      else if (const GamepadAxisEvent* e = event_cast_if<GamepadAxisEvent>(i))
      {
        last_axis_pos[e->axis] = e->amount;
      }
    }
  }
}