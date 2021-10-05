#include <core/math/spatial/point2.h>

namespace bones
{
  const Point2 Point2::zero   = Point2(0);
  const Point2 Point2::one    = Point2(1);
  const Point2 Point2::unit_x = Point2(1, 0);
  const Point2 Point2::unit_y = Point2(0, 1);

  Point2& Point2::operator=(const Point2& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const Point2& rhs)
  {
    os << "{ x: " << rhs.x << ", y: " << rhs.y << " }";
    return os;
  }

  bool operator==(const Point2& lhs, const Point2& rhs)
  {
    return (
      lhs.x == rhs.x &&
      lhs.y == rhs.y
    );
  }

  bool operator!=(const Point2& lhs, const Point2& rhs)
  {
    return (
      lhs.x != rhs.x ||
      lhs.y != rhs.y
    );
  }
}