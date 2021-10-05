#pragma once

#include <core/math/spatial/point2.h>
#include <core/math/spatial/rect.h>
#include <core/string/str.h>
#include <core/typedefs.h>
#include <platform/window.h>

#include <map>

namespace bones
{
  class Platform
  {
  // public:
  //   static Platform& get_instance()
  //   {
  //     static Platform instance;
  //     return instance;
  //   }

  private:
    std::map<u32, Ref<Window>> windows;
    bool gl_loaded = false;

  public:
    Platform();
    ~Platform();
    Platform(const Platform&) = delete;
    void operator=(const Platform&) = delete;

    Str name();
    Str gl_version();
    Str gl_renderer();

    void poll_events();

    Ref<Window> create_window(const Str& name, const Size2& size);
    Ref<Window> create_window(const Str& name, const Rect& bounds);
  };
}