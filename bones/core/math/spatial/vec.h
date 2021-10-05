#pragma once

#include <core/debug/assert.h>
#include <core/math/math.h>
#include <core/string/str.h>

#include <initializer_list>
#include <iostream>
#include <type_traits>

namespace bones
{
#pragma region "Vec Definitions"
  template<int N, typename T>
  struct Vec
  {
    T data[N];

    Vec() = default;
    Vec(T s);
    Vec(const std::initializer_list<T> args);

    const T& operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& rhs);
    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);
    Vec& operator*=(T rhs);
    Vec& operator/=(const Vec& rhs);
    Vec& operator/=(T rhs);
  };

  template <typename T>
  struct Vec<2, T>
  {
    union
    {
      struct { T x, y; };
      T data[2];
    };

    static const Vec zero;
    static const Vec one;
    static const Vec unit_x;
    static const Vec unit_y;

    Vec() = default;
    Vec(T s) : x(s), y(s) {}
    Vec(T x, T y) : x(x), y(y) {}
    Vec(const std::initializer_list<T> args);

    const T& operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& rhs);
    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);
    Vec& operator*=(T rhs);
    Vec& operator/=(const Vec& rhs);
    Vec& operator/=(T rhs);
  };
  using Vec2 = Vec<2, float>;
  using Vec2i = Vec<2, int>;
  using Vec2d = Vec<2, double>;

  template <typename T>
  struct Vec<3, T>
  {
    union
    {
      struct { T x, y, z; };
      T data[3];
    };

    static const Vec zero;
    static const Vec one;
    static const Vec unit_x;
    static const Vec unit_y;
    static const Vec unit_z;

    Vec() = default;
    Vec(T s) : x(s), y(s), z(s) {}
    Vec(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec(const std::initializer_list<T> args);

    const T& operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& rhs);
    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);
    Vec& operator*=(T rhs);
    Vec& operator/=(const Vec& rhs);
    Vec& operator/=(T rhs);
  };
  using Vec3 = Vec<3, float>;
  using Vec3i = Vec<3, int>;
  using Vec3d = Vec<3, double>;

  template <typename T>
  struct Vec<4, T>
  {
    union
    {
      struct { T x, y, z, w; };
      T data[4];
    };

    Vec() = default;
    Vec(T s) : x(s), y(s), z(s), w(s) {}
    Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vec(const std::initializer_list<T> args);

    const T& operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& rhs);
    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);
    Vec& operator*=(T rhs);
    Vec& operator/=(const Vec& rhs);
    Vec& operator/=(T rhs);
  };
  using Vec4 = Vec<4, float>;
  using Vec4i = Vec<4, int>;
  using Vec4d = Vec<4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, typename T>
  inline Vec<N, T>::Vec(T s)
  {
    for (int i = 0; i < N; i++)
      data[i] = s;
  }

  template<int N, typename T>
  inline Vec<N, T>::Vec(const std::initializer_list<T> args)
  {
    assert(args.size() <= N);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < N; ++it)
      data[i++] = *it;
  }

  template<int N, typename T>
  inline const T& Vec<N, T>::operator[](int i) const
  {
    assert(i >= 0 && i < N);
    return data[i];
  }

  template<int N, typename T>
  inline T& Vec<N, T>::operator[](int i)
  {
    assert(i >= 0 && i < N);
    return data[i];
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] = rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] += rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator-=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] -= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] *= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(T rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] *= rhs;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] /= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(T rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] /= rhs;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& rhs)
  {
    return rhs;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = -rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] + rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] - rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] * rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& lhs, T rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] * rhs;
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(T lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs * rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] / rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& lhs, T rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] / rhs;
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(T lhs, const Vec<N, T>& rhs)

  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs / rhs[i];
    return result;
  }

  template<int N, typename T>
  inline bool operator==(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      if (lhs[i] != rhs[i])
        return false;
    return true;
  }

  template<int N, typename T>
  inline bool operator!=(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      if (lhs[i] != rhs[i])
        return true;
    return false;
  }

  // NOTE: we do not account for large vectors when printing, use caution
  template<int N, typename T>
  inline std::ostream& operator<<(std::ostream& os, const Vec<N, T>& rhs)
  {
    Str format = (std::is_floating_point_v<T>) ? "%7.3f"
               : (std::is_integral_v<T>) ? "%7d"
               : "      NaN";

    os << "{ ";           
    for (int i = 0; i < N; i++)
    {
      T val = rhs[i];
      if (val >= 1e3 || (val <= 1e-3 && val != 0))
        os << format_s("%7.1e", val);
      else
        os << format_s(format, val);
      os << ", ";
    }
    os << "\b\b }";
    return os;
  }

#pragma endregion
#pragma region "Vec2 Methods"
  template<typename T> const Vec<2, T> Vec<2, T>::zero = Vec<2, T>(0);
  template<typename T> const Vec<2, T> Vec<2, T>::one = Vec<2, T>(1);
  template<typename T> const Vec<2, T> Vec<2, T>::unit_x = Vec<2, T>(1, 0);
  template<typename T> const Vec<2, T> Vec<2, T>::unit_y = Vec<2, T>(0, 1);
  
  template<typename T>
  inline Vec<2, T>::Vec(const std::initializer_list<T> args)
  {
    assert(args.size() <= 2);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 2; ++it)
      data[i++] = *it;
  }

  template<typename T>
  inline const T& Vec<2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return data[i];
  }

  template<typename T>
  inline T& Vec<2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return data[i];
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator=(const Vec<2, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(T rhs)
  {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(const Vec<2, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(T rhs)
  {
    x /= rhs;
    y /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Vec3 Methods"
  template<typename T> const Vec<3, T> Vec<3, T>::zero = Vec<3, T>(0);
  template<typename T> const Vec<3, T> Vec<3, T>::one = Vec<3, T>(1);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_x = Vec<3, T>(1, 0, 0);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_y = Vec<3, T>(0, 1, 0);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_z = Vec<3, T>(0, 0, 1);

  template<typename T>
  inline Vec<3, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
    assert(args.size() <= 3);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 3; ++it)
      data[i++] = *it;
  }

  template<typename T>
  inline const T& Vec<3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return data[i];
  }

  template<typename T>
  inline T& Vec<3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return data[i];
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator=(const Vec<3, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(T rhs)
  {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(const Vec<3, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(T rhs)
  {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Vec4 Methods"
  template<typename T>
  inline Vec<4, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
    assert(args.size() <= 4);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 4; ++it)
      data[i++] = *it;
  }

  template<typename T>
  inline const T& Vec<4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline T& Vec<4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator=(const Vec<4, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(T rhs)
  {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(const Vec<4, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(T rhs)
  {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Utility Methods"
  template<int N, typename T>
  inline T length_squared(const Vec<N, T>& rhs)
  {
    T result = 0;
    for (int i = 0; i < N; i++)
      result += (rhs[i] * rhs[i]);
    return result;
  }

  template<int N, typename T>
  inline T length(const Vec<N, T>& rhs)
  {
    return math::sqrt(length_squared(rhs));
  }

  template<int N, typename T>
  inline T distance_squared(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return length_squared(lhs - rhs);
  }

  template<int N, typename T>
  inline T distance(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return length(lhs - rhs);
  }

  template<int N, typename T>
  inline Vec<N, T> normalize(const Vec<N, T>& rhs)
  {
    return (rhs / length(rhs));
  }

  template<int N, typename T>
  inline T dot(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    T result = 0;
    for (int i = 0; i < N; i++)
      result += lhs[i] * rhs[i];
    return result;
  }

  template<typename T>
  inline Vec<3, T> cross(const Vec<3, T>& lhs, const Vec<3, T>& rhs)
  {
    return Vec<3, T>(
      lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.x * rhs.y - lhs.y * rhs.x
    );
  }

  template<int N, typename T>
  inline T angle(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return math::acos(dot(lhs, rhs) / (length(lhs) * length(rhs)));
  }

  template<typename T>
  inline Vec<2, T> perpendicular(const Vec<2, T>& rhs)
  {
    return Vec<2, T>(-rhs.y, rhs.x);
  }

  template<int N, typename T>
  inline Vec<N, T> reflect(const Vec<N, T>& vi, const Vec<N, T>& vn)
  {
    return vi - (2 * dot(vn, vi) * vn);
  }

  template<int N, typename T>
  inline Vec<N, T> refract(const Vec<N, T>& vi, const Vec<N, T>& vn, T eta)
  {
    T cosI = -dot(vn, vi);
    return eta * vi + (eta * cosI - math::sqrt(1 - eta * eta * (1 - cosI * cosI))) * vn;
  }

  template<int N, typename T>
  inline Vec<N, T> refract(const Vec<N, T>& vi, const Vec<N, T>& vn, T n1, T n2)
  {
    return refract(vi, vn, n1 / n2);
  }

  template<int N, typename T>
  inline Vec<N, T> faceforward(const Vec<N, T>& vi, const Vec<N, T>& vn, const Vec<N, T>& vref)
  {
    return (dot(vref, vi) < 0) ? vn : -vn;
  }

#pragma endregion
}