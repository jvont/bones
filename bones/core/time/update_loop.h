#pragma once

#include <core/typedefs.h>

namespace bones
{
  class UpdateLoop
  {
  private:
    bool is_running = false;

    unsigned int target_framerate = 60;
    u64 t_frame_target;
    u64 t_sum_max;
    double dt_fixed;

  protected:
    int max_frames = 5;
    double time_elapsed;

    virtual void initialize() {}
    virtual void update_fixed(double dt) {}
    virtual void update_variable(double dt) {}
    virtual void on_exit() {}
    
    void exit();

    void set_framerate(int framerate);
    int get_framerate();

  public:
    void run();
  };
}