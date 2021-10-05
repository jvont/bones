#pragma once

#include <core/math/spatial/mat.h>
#include <core/math/spatial/vec.h>

namespace bones
{
  class Camera
  {
    Mat4 view;
    bool is_dirty = true;

    Mat4 proj;
    Vec3 pos;

    Vec3 fwd = Vec3::unit_z;
    Vec3 up = Vec3::unit_y;

    // float zoom = 45.0f;

  public:
    Camera() : pos(Vec3::zero) {}
    Camera(Vec3 pos) : pos(pos) {}
    Camera(Vec3 pos, Vec3 fwd) : pos(pos), fwd(fwd) {}
    Camera(Vec3 pos, Vec3 fwd, Vec3 up) : pos(pos), fwd(fwd), up(up) {}

    // Move in camera frame (right-up-forward)
    void move(Vec3 amount);

    void set_position(Vec3 position);
    void look_at(Vec3 target);

    // void zoom_by(float amount);
    // void set_zoom(float amount);

    Mat4 get_view();
    Mat4 get_projection();
  };
}