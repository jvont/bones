<<<<<<< HEAD
=======
#include <core/debug/log.h>
#include <engine.h>

#include <glad/glad.h>

namespace bones
{
  void Engine::initialize()
  {
    set_framerate(60);

    logopen("log.txt");

    window = platform.create_window("Main1 Window", Size2(1200, 800));//(800, 480));
    window->add_handler(&input);

    // editor = window->create_editor();

    loginfo << "Platform: " << platform.name()        << logendl;
    loginfo                 << platform.gl_version()  << logendl;
    loginfo << "Renderer: " << platform.gl_renderer() << logendl;
  }

  void Engine::update_fixed(double dt)
  {
    platform.poll_events();
    
    if (input.pressed(Key::Escape))
      exit();
  }

  void Engine::update_variable(double dt)
  {
    Rect bounds = window->get_bounds();
    glViewport(0, 0, bounds.width, bounds.height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // editor->render();

    window->swap_buffers();
  }

  void Engine::on_exit()
  {

  }
}
>>>>>>> ba1829b803c371f8531676427c576c95be8ffc0d
