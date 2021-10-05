#pragma once
#ifdef PLATFORM_SDL

#include <core/typedefs.h>
#include <editor/editor.h>
#include <platform/window_sdl.h>

namespace bones
{
  class ImGuiEditor : public Editor
  {
  protected:

  public:
    ImGuiEditor(SDL_Window* wnd, SDL_GLContext ctx);
    ~ImGuiEditor();
    
    void render() override;
  };
}
#endif