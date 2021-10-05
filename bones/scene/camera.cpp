// #include <core/math/spatial/quat.h>
#include <core/math/math.h>
#include <scene/camera.h>

namespace bones
{
  void Camera::move(Vec3 amount)
  {
    Vec3 f = normalize(fwd);
    Vec3 s = cross(f, up);
    Vec3 u = cross(s, f);

    pos += s * amount.x;
    pos += u * amount.y;
    pos += f * amount.z;

    is_dirty = (amount != Vec3::zero);
  }

  void Camera::set_position(Vec3 value)
  {
    is_dirty = (pos != value);
    pos = value;
  }

  void Camera::look_at(Vec3 target)
  {
    Vec3 value = normalize(target - pos);
    is_dirty = (fwd != value);
    fwd = value;
  }

  Mat4 Camera::get_view()
  { 
    if (is_dirty)
      view = bones::look_at(pos, pos + fwd, up);

    return view;
  }

  Mat4 Camera::get_projection()
  {
    return Mat4::identity;
  }
}