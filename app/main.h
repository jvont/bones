#include <core/input/input_handler.h>
#include <core/time/update_loop.h>
#include <platform/platform.h>
#include <platform/window.h>

namespace bones
{
  class MainLoop : public UpdateLoop
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
