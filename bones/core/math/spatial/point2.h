#pragma once

#include <iostream>

namespace bones
{
  struct Point2
  {
    union
    {
      struct { int x, y; };
      struct { int width, height; };
    };

    static const Point2 zero;
    static const Point2 one;
    static const Point2 unit_x;
    static const Point2 unit_y;

    Point2() : x(0), y(0) {}
    Point2(int s) : x(s), y(s) {}
    Point2(int x, int y) : x(x), y(y) {}

    Point2& operator=(const Point2& rhs);
  };
  using Size2 = Point2;

  std::ostream& operator<<(std::ostream& os, const Point2& rhs);
  bool operator==(const Point2& lhs, const Point2& rhs);
  bool operator!=(const Point2& lhs, const Point2& rhs);
}