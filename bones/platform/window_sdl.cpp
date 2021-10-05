#ifdef PLATFORM_SDL

#include <core/debug/assert.h>
#include <core/typedefs.h>
#include <platform/window_sdl.h>

#include <editor/editor_imgui_sdl.h>

namespace bones
{
  // SDLWindow::SDLWindow()
  // {

  // }

  SDLWindow::~SDLWindow()
  {
    SDL_DestroyWindow(wnd);
    SDL_GL_DeleteContext(ctx);
  }

  Ref<Editor> SDLWindow::create_editor()
  {
    Ref<Editor> editor = create_ref<ImGuiEditor>(wnd, ctx);
    return editor;
  }

  void SDLWindow::make_current()
  {
    // assert()
    SDL_GL_MakeCurrent(wnd, ctx);
  }

  void SDLWindow::release_current()
  {
    // assert()
    SDL_GL_MakeCurrent(wnd, nullptr);
  }

  void SDLWindow::swap_buffers()
  {
    // assert()
    SDL_GL_SwapWindow(wnd);
  }
}
#endif