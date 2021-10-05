#include "main.h"

#include <core/debug/log.h>
#include <core/debug/profiler.h>

#include <glad/glad.h>

namespace bones
{
  void MainLoop::initialize()
  {
    set_framerate(120);

    logopen("log.txt");
    PROFILER_OPEN("profile.txt");

    window = platform.create_window("Main1 Window", Size2(1200, 800));//(800, 480));
    window->add_handler(&input);

    // editor = window->create_editor();

    loginfo << "Platform: " << platform.name()        << logendl;
    loginfo                 << platform.gl_version()  << logendl;
    loginfo << "Renderer: " << platform.gl_renderer() << logendl;
  }

  void MainLoop::update_fixed(double dt)
  {
    // PROFILE_SCOPE("fixed_update");

    platform.poll_events();

    if (input.pressed(Key::A))
      loginfo << "A" << logendl;
    
    if (input.pressed(MouseButton::Left))
      loginfo << "Left" << logendl;
    
    if (input.pressed(Key::Escape))
      exit();
  }

  void MainLoop::update_variable(double dt)
  {
    // PROFILE_SCOPE("variable_update");
    PROFILE_FUNC();

    Rect bounds = window->get_bounds();
    glViewport(0, 0, bounds.width, bounds.height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // editor->render();

    window->swap_buffers();
  }

  void MainLoop::on_exit()
  {

  }
}

int main()
{
  bones::MainLoop main_loop;
  main_loop.run();
  
  return 0;
}