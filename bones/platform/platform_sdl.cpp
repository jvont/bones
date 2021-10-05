#ifdef PLATFORM_SDL

#include <core/debug/assert.h>
#include <core/debug/log.h>
#include <core/events/event.h>
#include <core/math/spatial/point2.h>
#include <core/time/time.h>
#include <platform/platform.h>
#include <platform/window_sdl.h>

#include <backends/imgui_impl_sdl.h>
#include <glad/glad.h>
#include <SDL.h>

namespace bones
{
  // lookup table for SDL keys
  static const Key key_table[SDL_NUM_SCANCODES] = {
    Key::None, // 0
    Key::None, // 1-3
    Key::None,
    Key::None,
    Key::A, // 4-29
    Key::B,
    Key::C,
    Key::D,
    Key::E,
    Key::F,
    Key::G,
    Key::H,
    Key::I,
    Key::J,
    Key::K,
    Key::L,
    Key::M,
    Key::N,
    Key::O,
    Key::P,
    Key::Q,
    Key::R,
    Key::S,
    Key::T,
    Key::U,
    Key::V,
    Key::W,
    Key::X,
    Key::Y,
    Key::Z,
    Key::D1, // 30-39
    Key::D2,
    Key::D3,
    Key::D4,
    Key::D5,
    Key::D6,
    Key::D7,
    Key::D8,
    Key::D9,
    Key::D0,
    Key::Return, // 40-44
    Key::Escape,
    Key::Backspace,
    Key::Tab,
    Key::Space,
    Key::Minus, // 45-49
    Key::Equals,
    Key::LeftBracket,
    Key::RightBracket,
    Key::Backslash,
    Key::None, // 50 (non-US hash)
    Key::Semicolon, // 51-56
    Key::Apostrophe,
    Key::Grave,
    Key::Comma,
    Key::Period,
    Key::Slash,
    Key::CapsLock, // 57
    Key::F1, // 58-69
    Key::F2,
    Key::F3,
    Key::F4,
    Key::F5,
    Key::F6,
    Key::F7,
    Key::F8,
    Key::F9,
    Key::F10,
    Key::F11,
    Key::F12,
    Key::PrintScreen, // 70-82
    Key::ScrollLock,
    Key::Pause,
    Key::Insert,
    Key::Home,
    Key::PageUp,
    Key::Delete,
    Key::End,
    Key::PageDown,
    Key::Right,
    Key::Left,
    Key::Down,
    Key::Up,
    Key::NumLock, // 83
    Key::KPDivide, // 84-99
    Key::KPMultiply,
    Key::KPSubtract,
    Key::KPAdd,
    Key::KPEnter,
    Key::KP1,
    Key::KP2,
    Key::KP3,
    Key::KP4,
    Key::KP5,
    Key::KP6,
    Key::KP7,
    Key::KP8,
    Key::KP9,
    Key::KP0,
    Key::KPDecimal,
    Key::None, // 100 (non-US backslash)
    Key::Application, // 101 (windows context menu)
    Key::None, // 102 (power status)
    Key::KPEquals, // 103
    Key::F13, // 104-115
    Key::F14,
    Key::F15,
    Key::F16,
    Key::F17,
    Key::F18,
    Key::F19,
    Key::F20,
    Key::F21,
    Key::F22,
    Key::F23,
    Key::F24,
    Key::None, // 116-129 (special keys)
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None, // 130-132 (disabled keys)
    Key::None,
    Key::None,
    Key::None, // 133-134 (extra keypad)
    Key::None,
    Key::None, // 135-152 (language keys)
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None, // 153-164 (special keys)
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None, // 176-221 (extra keypad)
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None,
    Key::None, // 222-223 (disabled keys)
    Key::None,
    Key::LCtrl, // 224-231 (modifier keys)
    Key::LShift,
    Key::LAlt,
    Key::LGui,
    Key::RCtrl,
    Key::RShift,
    Key::RAlt,
    Key::RGui,
    Key::None // 232-SDL_NUM_SCANCODES (0-initialize the rest)
};

  Str Platform::name()
  {
    SDL_version v;
    SDL_GetVersion(&v); 
    return format_s("%s (SDL %d.%d.%d)", SDL_GetPlatform(), v.major, v.minor, v.patch);
  }

  Str Platform::gl_version()
  {
    if (gl_loaded)
      return format_s("OpenGL %s", (const char*)glGetString(GL_VERSION));
    else
      return "Could not get OpenGL version";
  }

  Str Platform::gl_renderer()
  {
    if (gl_loaded)
      return (const char*)glGetString(GL_RENDERER);
    else
      return "Could not get OpenGL renderer";
  }

  Platform::Platform()
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)//SDL_INIT_EVERYTHING) != 0)
    {
      logerror << "Failed to initialize SDL2: " << SDL_GetError() << logendl;
      return;
    }

    // configure OpenGL ver3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // core profile without backwards-compatible features
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // (at least) 5 bits RGB
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    // 24-bit depth buffer + 8-bit stencil (D24S8)
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // enable backbuffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  }

  Platform::~Platform()
  {
    SDL_Quit();
  }

  void Platform::poll_events()
  {
    // handle SDL events, dispatch to appropriate windows
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      // dispatch event to dearest imgui
      // ImGui_ImplSDL2_ProcessEvent(&event);

#pragma region "Window Events"
      if (event.type == SDL_QUIT)
      {
        loginfo << "Application quit event" << logendl;
      }
      else if (event.type == SDL_WINDOWEVENT)
      {
        switch (event.window.event)
        {
          case SDL_WINDOWEVENT_SHOWN:
            loginfo << "Window " << event.window.windowID << " shown" << logendl;
            break;
          case SDL_WINDOWEVENT_HIDDEN:
            loginfo << "Window " << event.window.windowID << " hidden" << logendl;
            break;
          case SDL_WINDOWEVENT_EXPOSED:
            loginfo << "Window " << event.window.windowID << " exposed" << logendl;
            break;
          case SDL_WINDOWEVENT_MOVED:
          {
            Rect& bounds = windows[event.window.windowID]->bounds;
            bounds.x = event.window.data1;
            bounds.y = event.window.data2;

            loginfo << "Window " << event.window.windowID << " moved to " 
                    << event.window.data1 << ',' << event.window.data2 << logendl;
            break;
          }
          case SDL_WINDOWEVENT_RESIZED:
          {
            Rect& bounds = windows[event.window.windowID]->bounds;
            bounds.width = event.window.data1;
            bounds.height = event.window.data2;

            loginfo << "Window " << event.window.windowID << " resized to " 
                    << event.window.data1 << 'x' << event.window.data2 << logendl;
            break;
          }
          case SDL_WINDOWEVENT_MINIMIZED:
            loginfo << "Window " << event.window.windowID << " minimized" << logendl;
            break;
          case SDL_WINDOWEVENT_MAXIMIZED:
            loginfo << "Window " << event.window.windowID << " maximized" << logendl;
            break;
          case SDL_WINDOWEVENT_RESTORED:
            loginfo << "Window " << event.window.windowID << " restored" << logendl;
            break;
          case SDL_WINDOWEVENT_ENTER:
            loginfo << "Window " << event.window.windowID << " gained mouse focus" << logendl;
            break;
          case SDL_WINDOWEVENT_LEAVE:
            loginfo << "Window " << event.window.windowID << " lost mouse focus" << logendl;
            break;
          case SDL_WINDOWEVENT_FOCUS_GAINED:
            loginfo << "Window " << event.window.windowID << " gained keyboard focus" << logendl;
            break;
          case SDL_WINDOWEVENT_FOCUS_LOST:
            loginfo << "Window " << event.window.windowID << " lost keyboard focus" << logendl;
            break;
          case SDL_WINDOWEVENT_CLOSE:
            loginfo << "Window " << event.window.windowID << " closed" << logendl;
            break;
          default:
            loginfo << "Window " << event.window.windowID << " got unknown event " << event.window.event << logendl;
            break;
        }
      }
#pragma endregion
#pragma region "Keyboard Events"
      else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
      {
        KeyEvent e;
        e.key = key_table[event.key.keysym.scancode];
        if (e.key != Key::None)
        {
          u16 sdl_keymod = event.key.keysym.mod;
          u16 keymod = 0;
          if (!(sdl_keymod & KMOD_NONE))
          {
            if (sdl_keymod & KMOD_LSHIFT)
              keymod |= static_cast<u16>(KeyMod::LShift);
            if (sdl_keymod & KMOD_RSHIFT)
              keymod |= static_cast<u16>(KeyMod::RShift);

            if (sdl_keymod & KMOD_LCTRL)
              keymod |= static_cast<u16>(KeyMod::LCtrl);
            if (sdl_keymod & KMOD_RCTRL)
              keymod |= static_cast<u16>(KeyMod::RCtrl);
            
            if (sdl_keymod & KMOD_LALT)
              keymod |= static_cast<u16>(KeyMod::LAlt);
            if (sdl_keymod & KMOD_RALT)
              keymod |= static_cast<u16>(KeyMod::RAlt);
            
            if (sdl_keymod & KMOD_LGUI)
              keymod |= static_cast<u16>(KeyMod::LGui);
            if (sdl_keymod & KMOD_RGUI)
              keymod |= static_cast<u16>(KeyMod::RGui);

            if (sdl_keymod & KMOD_NUM)
              keymod |= static_cast<u16>(KeyMod::Num);
            if (sdl_keymod & KMOD_CAPS)
              keymod |= static_cast<u16>(KeyMod::Caps);
            if (sdl_keymod & KMOD_MODE)
              keymod |= static_cast<u16>(KeyMod::AltGr);
          }
          e.mod = static_cast<KeyMod>(keymod);
          e.pressed = (event.type == SDL_KEYDOWN);
          e.repeat = (event.key.repeat);

          windows[event.key.windowID]->handle_event(e);

          // loginfo << "Keypress Event:" << std::endl
          //         << "\tscancode: " << static_cast<int>(e.key) << std::endl
          //         << "\tmodifier: " << static_cast<int>(e.mod) << std::endl
          //         << "\tpressed:  " << e.pressed << std::endl
          //         << "\trepeat:    " << e.repeat << std::endl
          //         << "\tkeycode:  " << static_cast<char>(e.key) << logendl;
        }
      }
      else if (event.type == SDL_TEXTEDITING)
      {
      }
      else if (event.type == SDL_TEXTINPUT)
      {
      }
#pragma endregion
#pragma region "Mouse Events"
      else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
      {
        MouseButtonEvent e;
        u8 sdl_button = event.button.button;
        switch (sdl_button)
        {
          case SDL_BUTTON_LEFT:
            e.button = MouseButton::Left;
            break;
          case SDL_BUTTON_MIDDLE:
            e.button = MouseButton::Middle;
            break;
          case SDL_BUTTON_RIGHT:
            e.button = MouseButton::Right;
            break;
          case SDL_BUTTON_X1:
            e.button = MouseButton::X1;
            break;
          case SDL_BUTTON_X2:
            e.button = MouseButton::X2;
            break;
          default:
            e.button = MouseButton::None;
            break;
        }
        if (e.button != MouseButton::None)
        {
          e.pos = Point2(event.button.x, event.button.y);
          e.pressed = (event.type == SDL_MOUSEBUTTONDOWN);
          e.clicks = event.button.clicks;

          windows[event.button.windowID]->handle_event(e);

          // loginfo << "Mouse button press event:" << std::endl
          //         << "\tbutton:  " << static_cast<int>(e.button) << std::endl
          //         << "\tpos:     " << e.pos << std::endl
          //         << "\tpressed: " << e.pressed << std::endl
          //         << "\trepeat:  " << (int)e.clicks << logendl;
        }
      }
      else if (event.type == SDL_MOUSEMOTION)
      {
        u8 button = 0;
        u32 sdl_button = event.motion.state;
        if (sdl_button & SDL_BUTTON_LMASK)
          button |= static_cast<u8>(MouseButton::Left);
        if (sdl_button & SDL_BUTTON_MMASK)
          button |= static_cast<u8>(MouseButton::Middle);
        if (sdl_button & SDL_BUTTON_RMASK)
          button |= static_cast<u8>(MouseButton::Right);
        if (sdl_button & SDL_BUTTON_X1MASK)
          button |= static_cast<u8>(MouseButton::X1);
        if (sdl_button & SDL_BUTTON_X2MASK)
          button |= static_cast<u8>(MouseButton::X2);

        MouseMotionEvent e;
        e.button = static_cast<MouseButton>(button);
        e.pos = Point2(event.motion.x, event.motion.y);
        e.delta = Point2(event.motion.xrel, event.motion.yrel);

        windows[event.motion.windowID]->handle_event(e);

        // loginfo << "Mouse motion event:" << std::endl
        //         << "\tbutton:  " << static_cast<int>(e.button) << std::endl
        //         << "\tpos:     " << e.pos << std::endl
        //         << "\tpressed: " << e.delta << logendl;
      }
      else if (event.type == SDL_MOUSEWHEEL)
      {
        MouseScrollEvent e;
        e.amount = event.wheel.y;

        windows[event.wheel.windowID]->handle_event(e);

        // loginfo << "Mouse scroll event:" << std::endl
        //         << "\tamount: " << e.amount << logendl;
      }
#pragma endregion
#pragma region "Controller Events"
      else if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
      {
        loginfo << "Controller button pressed" << logendl;
      }
      else if (event.type == SDL_CONTROLLERAXISMOTION)
      {
        loginfo << "Controller axis motion" << logendl;
      }
      else if (event.type == SDL_CONTROLLERDEVICEADDED)
      {
        loginfo << "Controller " << event.cdevice.which << " added" << logendl;
      }
      
      else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
      {
        loginfo << "Controller " << event.cdevice.which << " removed" << logendl;
      }
      else if (event.type == SDL_CONTROLLERDEVICEREMAPPED)
      {
        loginfo << "Controller " << event.cdevice.which << " remapped" << logendl;
      }
#pragma endregion
    }
  }

  Ref<Window> Platform::create_window(const Str& name, const Size2& size)
  {
    return create_window(name, Rect(Point2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), size));
  }

  Ref<Window> Platform::create_window(const Str& name, const Rect& bounds)
  {
    int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    SDL_Window* wnd = SDL_CreateWindow(name.c_str(), bounds.x, bounds.y, bounds.width, bounds.height, flags);
    if (wnd == nullptr)
    {
      logerror << "Failed to create SDL window: " << SDL_GetError() << logendl;
      return nullptr;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(wnd);
    if (ctx == nullptr)
    {
      logerror << "Failed to create OpenGL context: " << SDL_GetError() << logendl;
      return nullptr;
    }

    // enable vsync
    if (SDL_GL_SetSwapInterval(-1) < 0)
    {
      logwarn << "Failed to enable adaptive vsync: " << SDL_GetError() << logendl;
      if (SDL_GL_SetSwapInterval(1) < 0)
      {
        logerror << "Failed to enable vsync: " << SDL_GetError() << logendl;
      }
    }

    // load OpenGL functions
    if (!gl_loaded)
    {
      if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
      {
        logerror << "Failed to initialize GLAD" << logendl;
        return nullptr;
      }
      
      glEnable(GL_DEPTH_TEST);
      gl_loaded = true;
    }

    // get true window position
    Rect bounds_actual;
    SDL_GetWindowPosition(wnd, &bounds_actual.x, &bounds_actual.y);
    bounds_actual.size = bounds.size;

    // create/store window
    Ref<SDLWindow> window = create_ref<SDLWindow>();
    window->bounds = bounds_actual;
    window->wnd = wnd;
    window->ctx = ctx;
    u32 id = SDL_GetWindowID(wnd);
    windows[id] = window;

    // set window default properties
    SDL_SetWindowResizable(wnd, SDL_TRUE);
    // SDL_SetWindowMinimumSize(wnd, bounds.width, bounds.height);

    // set relative mouse mode
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    return window;
  }
}
#endif