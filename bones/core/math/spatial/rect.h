#pragma once

#include <core/math/spatial/point2.h>

#include <iostream>

namespace bones
{
  struct Rect
  {
    union
    {
      struct { int x, y; };
      Point2 pos;
    };
    union
    {
      struct { int width, height; };
      Size2 size;
    };

    Rect() : x(0), y(0), width(0), height(0) {}
    Rect(int w, int h) : x(0), y(0), width(w), height(h) {}
    Rect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    Rect(Point2 pos, Size2 size) : pos(pos), size(size) {}

    inline int left() const { return x; };
    inline int bottom() const { return y; };
    inline int right() const { return x + width; };
    inline int top() const { return y + height; };

    bool contains(const Point2& p) const;
    bool contains(const Rect& r) const;
    bool intersects(const Rect& r) const;

    Rect& operator=(const Rect& r);
  };

  Rect bounding_box(const Rect& r1, const Rect& r2);

  std::ostream& operator<<(std::ostream& os, const Rect& rhs);
  bool operator==(const Rect& r1, const Rect& r2);
  bool operator!=(const Rect& r1, const Rect& r2);
}