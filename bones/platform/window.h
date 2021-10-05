#pragma once

#include <core/events/event_handler.h>
#include <core/math/spatial/rect.h>
#include <editor/editor.h>

namespace bones
{
  class Window : public EventHandler
  {
    friend class Platform;

  protected:
    Rect bounds;

    Window(const Rect& bounds) : bounds(bounds) {}

  public:
    Window() = default;
    ~Window() = default;
    
    const Rect& get_bounds() const { return bounds; }

    virtual Ref<Editor> create_editor() = 0;

    virtual void make_current() = 0;
    virtual void release_current() = 0;
    virtual void swap_buffers() = 0;
  };
}