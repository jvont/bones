<<<<<<< HEAD
=======
#include <core/input/input_handler.h>
#include <core/time/update_loop.h>
#include <platform/platform.h>
#include <platform/window.h>

namespace bones
{
  class Engine : public UpdateLoop
  {
    Platform platform;
    
    Ref<Window> window;
    InputHandler input;

    // Ref<Editor> editor;
    
    void initialize() override;
    void update_fixed(double dt) override;
    void update_variable(double dt) override;
    void on_exit() override;
  };
}
>>>>>>> ba1829b803c371f8531676427c576c95be8ffc0d
