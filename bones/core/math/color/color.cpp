#include <core/math/color/color.h>

namespace bones
{
  Color Color::hex_rgb(u32 hex)
  {
    return Color(
      ((hex >> 16) & 0xFF) / 255.0f,
      ((hex >> 8) & 0xFF) / 255.0f,
      ((hex) & 0xFF) / 255.0f,
      1.0f
    );
  }

  Color Color::hex_argb(u32 hex)
  {
    return Color(
      ((hex >> 16) & 0xFF) / 255.0f,
      ((hex >> 8) & 0xFF) / 255.0f,
      ((hex) & 0xFF) / 255.0f,
      ((hex >> 24) & 0xFF) / 255.0f
    );
  }

  // Str Color::to_string() const
  // {
  //   char buf[16], *ptr = buf;
  //   ptr += std::snprintf(ptr, sizeof(buf) - (ptr - buf), "(%3d, %3d, %3d)", r, g, b);
  //   return Str(buf);
  // }

  // static Color from_hsv(u32 hsv, float a);
  // static Color from_hsv(u32 hsv);

  // u32 hex() const;

  // Color hsv() const;
  // Vec3 hsv() const;

  // u8 h() const;
  // u8 s() const;
  // u8 v() const;

  Color& Color::operator=(const Color& rhs)
  {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
    return *this;
  }

  Color& Color::operator+=(const Color& rhs)
  {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;
    return *this;
  }

  Color& Color::operator-=(const Color& rhs)
  {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;
    return *this;
  }

  Color& Color::operator*=(const Color& rhs)
  {
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;
    return *this;
  }

  Color& Color::operator*=(float rhs)
  {
    r *= rhs;
    g *= rhs;
    b *= rhs;
    a *= rhs;
    return *this;
  }

  Color& Color::operator/=(const Color& rhs)
  {
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;
    return *this;
  }

  Color& Color::operator/=(float rhs)
  {
    r /= rhs;
    g /= rhs;
    b /= rhs;
    a /= rhs;
    return *this;
  }

  Color operator+(const Color& rhs)
  {
    return rhs;
  }

  Color operator-(const Color& rhs)
  {
    return Color(
      -rhs.r,
      -rhs.g,
      -rhs.b,
      -rhs.a
    );
  }

  Color operator+(const Color& lhs, const Color& rhs)
  {
    return Color(
      lhs.r + rhs.r,
      lhs.g + rhs.g,
      lhs.b + rhs.b,
      lhs.a + rhs.a
    );
  }

  Color operator-(const Color& lhs, const Color& rhs)
  {
    return Color(
      lhs.r - rhs.r,
      lhs.g - rhs.g,
      lhs.b - rhs.b,
      lhs.a - rhs.a
    );
  }

  Color operator*(const Color& lhs, const Color& rhs)
  {
    return Color(
      lhs.r * rhs.r,
      lhs.g * rhs.g,
      lhs.b * rhs.b,
      lhs.a * rhs.a
    );
  }

  Color operator*(const Color& lhs, float rhs)
  {
    return Color(
      lhs.r * rhs,
      lhs.g * rhs,
      lhs.b * rhs,
      lhs.a * rhs
    );
  }

  Color operator*(float lhs, const Color& rhs)
  {
    return Color(
      lhs * rhs.r,
      lhs * rhs.g,
      lhs * rhs.b,
      lhs * rhs.a
    );
  }

  Color operator/(const Color& lhs, const Color& rhs)
  {
    return Color(
      lhs.r / rhs.r,
      lhs.g / rhs.g,
      lhs.b / rhs.b,
      lhs.a / rhs.a
    );
  }

  Color operator/(const Color& lhs, float rhs)
  {
    return Color(
      lhs.r / rhs,
      lhs.g / rhs,
      lhs.b / rhs,
      lhs.a / rhs
    );
  }

  Color operator/(float lhs, const Color& rhs)
  {
    return Color(
      lhs / rhs.r,
      lhs / rhs.g,
      lhs / rhs.b,
      lhs / rhs.a
    );
  }

  bool operator==(const Color& lhs, const Color& rhs)
  {
    return (
      lhs.r == rhs.r &&
      lhs.g == rhs.g &&
      lhs.b == rhs.b &&
      lhs.a == rhs.a
    );
  }

  bool operator!=(const Color& lhs, const Color& rhs)
  {
    return (
      lhs.r != rhs.r ||
      lhs.g != rhs.g ||
      lhs.b != rhs.b ||
      lhs.a != rhs.a
    );
  }
}