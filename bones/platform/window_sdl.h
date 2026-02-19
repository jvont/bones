#pragma once
#ifdef PLATFORM_SDL

#include <platform/window.h>

#include <SDL3/SDL.h>

namespace bones
{
  class SDLWindow : public Window
  {
    friend class Platform;

  private:
    SDL_Window* wnd;
    SDL_GLContext ctx;

  public:
    SDLWindow() = default;
    ~SDLWindow();

    Ref<Editor> create_editor() override;

    void make_current() override;
    virtual void release_current() override;
    virtual void swap_buffers() override;
  };
}
#endif