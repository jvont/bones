#include <core/time/time.h>
#include <core/time/update_loop.h>

// main loop is based on: https://gafferongames.com/post/fix_your_timestep/

namespace bones
{
  void UpdateLoop::run()
  {
    set_framerate(target_framerate);

    is_running = true;
    initialize();

    u64 t_start = time::nanos();
    u64 t_prev = t_start;
    u64 t_sum = 0; // integrate time

    while (is_running)
    {
      u64 t_curr = time::nanos();
      time_elapsed = (t_start - t_curr) / 1e9;

      u64 t_frame = t_curr - t_prev;
      t_prev = t_curr;
      t_sum += t_frame;

      // saturate error to prevent the spiral of death
      if (t_sum > t_sum_max)
        t_sum = t_sum_max;

      // fixed timestep update
      while (t_sum >= t_frame_target)
      {
        t_sum -= t_frame_target;
        update_fixed(dt_fixed);
      }

      // variable timestep update
      // calculate dt based on previous frame update
      double dt = t_frame / 1e9;
      update_variable(dt);
    }
    
    on_exit();
  }

  void UpdateLoop::exit()
  {
    is_running = false;
  }

  void UpdateLoop::set_framerate(int framerate)
  {
    target_framerate = framerate;
    t_frame_target = (u64)(1e9 / target_framerate);
    t_sum_max = max_frames * t_frame_target;
    dt_fixed = 1.0 / target_framerate;
  }
  
  int UpdateLoop::get_framerate()
  {
    return target_framerate;
  }
}