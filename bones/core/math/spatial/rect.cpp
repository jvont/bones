#include <core/math/spatial/rect.h>

namespace bones
{
  Rect& Rect::operator=(const Rect& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    width = rhs.width;
    height = rhs.height;
    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const Rect& rhs)
  {
    os << "{ x: " << rhs.x << ", y: " << rhs.y << ", w: " << rhs.width << ", h: " << rhs.height << " }";
    return os;
  }

  bool operator==(const Rect& lhs, const Rect& rhs)
  {
    return (
      lhs.x == rhs.x &&
      lhs.y == rhs.y &&
      lhs.width == rhs.width &&
      lhs.height == rhs.height
    );
  }

  bool operator!=(const Rect& lhs, const Rect& rhs)
  {
    return (
      lhs.x != rhs.x ||
      lhs.y != rhs.y ||
      lhs.width != rhs.width ||
      lhs.height != rhs.height
    );
  }
}