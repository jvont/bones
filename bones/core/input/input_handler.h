#pragma once

#include <core/events/event_handler.h>
#include <core/events/event.h>
#include <core/input/gamepad.h>
#include <core/input/keyboard.h>
#include <core/input/mouse.h>
#include <core/string/str.h>

#include <map>
#include <set>

namespace bones
{
  class InputMap
  {
    // std::map<Str, Action> event_map;

  };

  class InputHandler : public EventHandler
  {
  protected:
    std::set<Key> active_keys;

    std::set<MouseButton> active_mouse_buttons;
    Point2 last_mouse_pos;

    std::set<GamepadButton> active_gamepad_buttons;
    std::map<GamepadAxis, Point2> last_axis_pos;

  public:
    bool pressed(Key key);
    bool released(Key key);

    bool pressed(MouseButton button);
    bool released(MouseButton button);
    Point2 get_mouse() const;

    bool pressed(GamepadButton button);
    bool released(GamepadButton button);
    Point2 get_axis(GamepadAxis axis) const;

    // bool pressed(const Str& action);
    // bool released(const Str& action);

    void handle_event(const Event& event) override;
  };
}