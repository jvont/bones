#pragma once

#include <core/debug/assert.h>
#include <core/math/math.h>
#include <core/math/spatial/vec.h>
#include <core/string/str.h>

#include <initializer_list>
#include <iostream>
#include <type_traits>

namespace bones
{
#pragma region "Mat Definitions"
  // Matrices are stored in row-major format, where NxM denotes N rows and M columns.
  template<int N, int M, typename T>
  struct Mat
  {
    union
    {
      Vec<M, T> row[N];
      T data[N][M];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    const Vec<N, T>& operator[](int i) const;
    Vec<N, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };

  // prevent 1-dimensional matrices
  template<int N, typename T> struct Mat<N, 1, T>;
  template<int M, typename T> struct Mat<1, M, T>;
  template<typename T> struct Mat<1, 1, T>;

  template<typename T>
  struct Mat<2, 2, T>
  {
    union
    {
      Vec<2, T> row[2];
      T data[2][2];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    const Vec<2, T>& operator[](int i) const;
    Vec<2, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat2 = Mat<2, 2, float>;
  using Mat2i = Mat<2, 2, int>;
  using Mat2d = Mat<2, 2, double>;

  template<typename T>
  struct Mat<3, 3, T>
  {
    union
    {
      Vec<3, T> row[3];
      T data[3][3];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    const Vec<3, T>& operator[](int i) const;
    Vec<3, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat3 = Mat<3, 3, float>;
  using Mat3i = Mat<3, 3, int>;
  using Mat3d = Mat<3, 3, double>;

  template<typename T>
  struct Mat<4, 4, T>
  {
    union
    {
      Vec<4, T> row[4];
      T data[4][4];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    const Vec<4, T>& operator[](int i) const;
    Vec<4, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat4 = Mat<4, 4, float>;
  using Mat4i = Mat<4, 4, int>;
  using Mat4d = Mat<4, 4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, int M, typename T> Mat<N, M, T> Mat<N, M, T>::diag(T diag_val)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = (r == c) ? diag_val : 0;
    return result;
  }

  template<int N, int M, typename T> Mat<N, M, T> Mat<N, M, T>::full(T fill_val)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<int N, int M, typename T> const Mat<N, M, T> Mat<N, M, T>::identity = Mat<N, M, T>::diag(1);
  template<int N, int M, typename T> const Mat<N, M, T> Mat<N, M, T>::zero = Mat<N, M, T>::full(0);

  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= N * M);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= M)
      {
        r++;
        c = 0;
      }
    }
  }
  
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= N);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= M);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
        data[r++][c] = *it2;
      r++;
    }
  }

  template<int N, int M, typename T>
  inline const Vec<N, T>& Mat<N, M, T>::operator[](int i) const
  {
    assert(i >= 0 && i < N);
    return row[i];
  }

  template<int N, int M, typename T>
  inline Vec<N, T>& Mat<N, M, T>::operator[](int i)
  {
    assert(i >= 0 && i < N);
    return row[i];
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      row[r] = rhs[r];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] += rhs[r][c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] -= rhs[r][c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<N, M, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(T rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator/=(T rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] /= rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& rhs)
  {
    return rhs;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = -rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] + rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] - rhs[r][c];
    return result;
  }

  template<int N, int M, int O, typename T>
  inline Mat<N, O, T> operator*(const Mat<N, M, T>& lhs, const Mat<M, O, T>& rhs)
  {
    Mat<N, O, T> result;
    for (int r = 0; r < N; r++)
    {
      for (int c = 0; c < O; c++)
      {
        T val = 0;
        for (int i = 0; i < M; i++)
          val += lhs[r][i] * rhs[i][c];
        result[r][c] = val;
      }
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator*(const Mat<N, M, T>& lhs, T rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] * rhs;
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator*(T lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs * rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline Vec<N, T> operator*(const Mat<N, M, T>& lhs, const Vec<M, T>& rhs)
  {
    Vec<N, T> result;
    for (int r = 0; r < N; r++)
    {
      T val = 0;
      for (int c = 0; c < M; c++)
        val += lhs[r][c] * rhs[c];
      result[r] = val;
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator/(const Mat<N, M, T>& lhs, T rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] / rhs;
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator/(T lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs / rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline bool operator==(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        if (lhs[r][c] != rhs[r][c])
          return false;
    return true;
  }

  template<int N, int M, typename T>
  inline bool operator!=(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        if (lhs[r][c] != rhs[r][c])
          return true;
    return false;
  }

  // NOTE: we do not account for large matrices when printing, use caution
  template<int N, int M, typename T>
  inline std::ostream& operator<<(std::ostream& os, const Mat<N, M, T>& rhs)
  {
    Str format = (std::is_floating_point_v<T>) ? "%7.3f"
               : (std::is_integral_v<T>) ? "%7d"
               : "      NaN";

    for (int r = 0; r < N; r++)
    {
      os << "| ";
      for (int c = 0; c < M; c++)
      {
        T val = rhs[r][c];
        if (val >= 1e3 || (val <= 1e-3 && val != 0))
          os << format_s("%7.1e", val);
        else
          os << format_s(format, val);
        os << ", ";
      }
      os << "\b\b |";
      if (r < N - 1)
        os << "\n";
    }
    return os;
  }

#pragma endregion
#pragma region "Mat2 Methods"
  template<typename T> Mat<2, 2, T> Mat<2, 2, T>::diag(T diag_val)
  {
    Mat<2, 2, T> result;
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<2, 2, T> Mat<2, 2, T>::full(T fill_val)
  {
    Mat<2, 2, T> result;
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::identity = Mat<2, 2, T>::diag(1);
  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::zero = Mat<2, 2, T>::full(0);

  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 2)
      {
        r++;
        c = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 2);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 2);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline const Vec<2, T>& Mat<2, 2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return row[i];
  }

  template<typename T>
  inline Vec<2, T>& Mat<2, 2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return row[i];
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      row[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator+=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] += rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator-=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] -= rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(const Mat<2, 2, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat3 Methods"
  template<typename T> Mat<3, 3, T> Mat<3, 3, T>::diag(T diag_val)
  {
    Mat<3, 3, T> result;
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<3, 3, T> Mat<3, 3, T>::full(T fill_val)
  {
    Mat<3, 3, T> result;
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::identity = Mat<3, 3, T>::diag(1);
  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::zero = Mat<3, 3, T>::full(0);

  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 9);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 3)
      {
        r++;
        c = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 3);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 3);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline const Vec<3, T>& Mat<3, 3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return row[i];
  }

  template<typename T>
  inline Vec<3, T>& Mat<3, 3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return row[i];
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      row[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator+=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] += rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator-=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] -= rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(const Mat<3, 3, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat4 Methods"
  template<typename T> Mat<4, 4, T> Mat<4, 4, T>::diag(T diag_val)
  {
    Mat<4, 4, T> result;
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<4, 4, T> Mat<4, 4, T>::full(T fill_val)
  {
    Mat<4, 4, T> result;
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        result[r][c] = fill_val;
    return result;
  }
  
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::identity = Mat<4, 4, T>::diag(1);
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::zero = Mat<4, 4, T>::full(0);

  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 16);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 4)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 4);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 4);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline const Vec<4, T>& Mat<4, 4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return row[i];
  }

  template<typename T>
  inline Vec<4, T>& Mat<4, 4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return row[i];
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      row[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator+=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] += rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator-=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] -= rhs[r][c];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(const Mat<4, 4, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Utility Methods"
  template<int N, int M, typename T>
  inline Mat<N, M, T> transpose(const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = rhs[c][r];
    return result;
  }

  // returns the submatrix obtained by removing row, col
  template<int N, typename T>
  inline Mat<N-1, N-1, T> submatrix(const Mat<N, N, T>& rhs, int row, int col)
  {
    assert(row >= 0 && row < N);
    assert(col >= 0 && col < N);

    Mat<N-1, N-1, T> result;
    int i = 0, j = 0;
    for (int r = 0; r < N; r++)
    {
      for (int c = 0; c < N; c++)
      {
        if (r != row && c != col)
          result[i][j++] = rhs[r][c];
        
        if (j == N - 1)
        {
          j = 0;
          i++;
        }
      }
    }
    return result;
  }

  template<typename T>
  inline Mat<2, 2, T> cofactor(const Mat<2, 2, T>& rhs)
  {
    return Mat<2, 2, T>({
      {rhs[1][1], -rhs[0][1]},
      {-rhs[1][0], rhs[0][0]}
    });
  }

  template<int N, typename T>
  inline Mat<N, N, T> cofactor(const Mat<N, N, T>& rhs)
  {
    Mat<N, N, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < N; c++)
        result[r][c] = (1 - 2 * ((r + c) % 2)) * determinant(submatrix(rhs, r, c));
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> adjoint(const Mat<N, N, T>& rhs)
  {
    return transpose(cofactor(rhs));
  }

  template<typename T>
  inline T determinant(const Mat<2, 2, T>& rhs)
  {
    return (rhs[0][0] * rhs[1][1] - rhs[0][1] * rhs[1][0]);
  }

  template<typename T>
  inline T determinant(const Mat<3, 3, T>& rhs)
  {
    return (
      rhs[0][0] * (rhs[1][1] * rhs[2][2] - rhs[2][1] * rhs[1][2]) -
      rhs[1][0] * (rhs[0][1] * rhs[2][2] - rhs[2][1] * rhs[0][2]) +
      rhs[2][0] * (rhs[0][1] * rhs[1][2] - rhs[1][1] * rhs[0][2])
    );
  }

  // generic determinant method (slow). currently gets called for 4x4 matrices
  template<int N, typename T>
  inline T determinant(const Mat<N, N, T>& rhs)
  {
    T result = 0;
    for (int c = 0; c < N; c++)
      result += (1 - 2 * (c % 2)) * rhs[0][c] * determinant(submatrix(rhs, 0, c));
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> inverse(const Mat<N, N, T>& rhs)
  {
    T det = determinant(rhs);
    // if (approx_equal(det, T(0.0f)))
    if (det == 0)
      return Mat<N, N, T>::zero;

    return (adjoint(rhs) / determinant(rhs));
  }

  template<typename T>
  inline Mat<3, 3, T> scale(const Vec<2, T>& scaling)
  {
    Mat<3, 3, T> result;
    for (int i = 0; i < 2; i++)
      result[i][i] *= scaling[i];
    return result;
  }

  template<typename T>
  inline void scale(Mat<3, 3, T>& result, const Vec<2, T>& scaling)
  {
    for (int i = 0; i < 2; i++)
      result[i][i] *= scaling[i];
  }

  template<typename T>
  inline Mat<4, 4, T> scale(const Vec<3, T>& scaling)
  {
    Mat<4, 4, T> result;
    for (int i = 0; i < 3; i++)
      result[i][i] *= scaling[i];
    return result;
  }

  template<typename T>
  inline void scale(Mat<4, 4, T>& result, const Vec<3, T>& scaling)
  {
    for (int i = 0; i < 3; i++)
      result[i][i] *= scaling[i];
  }

  template<typename T>
  inline Mat<4, 4, T> rotate(const Vec<3, T>& axis, T angle)
  {
    const T c = math::cos(angle);
    const T s = math::sin(angle);

    const Vec<3, T> ax = normalize(axis);
    const Vec<3, T> tax = ((1 - c) * ax);

    return Mat<4, 4, T>({
      {tax.x * ax.x + c,        tax.y * ax.x - s * ax.z, tax.z * ax.x + s * ax.y, 0},
      {tax.x * ax.y + s * ax.z, tax.y * ax.y + c,        tax.z * ax.y - s * ax.x, 0},
      {tax.x * ax.z - s * ax.y, tax.y * ax.z + s * ax.x, tax.z * ax.z + c,        0},
      {0,                       0,                       0,                       1}
    });
  }

  template<typename T>
  inline Mat<4, 4, T> rotate(Mat<4, 4, T>& result, const Vec<3, T>& axis, T angle)
  {
    result *= rotate(axis, angle);
  }

  template<typename T>
  inline Mat<4, 4, T> translate(Vec<3, T> distance)
  {
    return Mat<4, 4, T>({
      {1, 0, 0, distance.x},
      {0, 1, 0, distance.y},
      {0, 0, 1, distance.z},
      {0, 0, 0, 1         }
    });
  }

  template<typename T>
  inline void translate(Mat<4, 4, T>& result, Vec<3, T> distance)
  {
    result *= translate(distance);
  }

  // calculates transformation matrix based on absolute positions
  template<typename T>
  inline Mat<4, 4, T> look_at(const Vec<3, T>& eye, const Vec<3, T>& target, const Vec<3, T>& up = Vec<3, T>::unit_y)
  {
    Vec<3, T> f = normalize(target - eye);
    Vec<3, T> r = normalize(cross(up, f));
    Vec<3, T> u = cross(f, r);

    Mat<4, 4, T> rot({
      {r.x, u.x, f.x, 0},
      {r.y, u.y, f.y, 0},
      {r.z, u.z, f.z, 0},
      {0,   0,   0,   1}
    });
    return (rot * translate(eye));
  }

  template<typename T>
  inline Mat<4, 4, T> orthographic(T left, T right, T top, T bottom, T near, T far)
  {
    return Mat<4, 4, T>({
      {2 / (right - left), 0,                  0,                                -(right + left) / (right - left)},
      {0,                  2 / (top - bottom), 0,                                -(top + bottom) / (top - bottom)},
      {0,                  0,                  -2 / (far - near),                -(far + near) / (far - near)    },
      {0,                  0,                  0,                                1                               }
    });
  }

  template<typename T>
  inline Mat<4, 4, T> orthographic(T width, T height, T near, T far)
  {
    return Mat<4, 4, T>({
      {2 / width,    0,          0,                 0                           },
      {0,            2 / height, 0,                 0                           },
      {0,            0,          -2 / (far - near), -(far + near) / (far - near)},
      {0,            0,          0,                 1                           }
    });
  }

  template<typename T>
  inline Mat<4, 4, T> perspective(T left, T right, T top, T bottom, T near, T far)
  {
    return Mat<4, 4, T>({
      {2 * near / (right - left), 0,                         (right + left) / (right - left),   0                             },
      {0,                         2 * near / (top - bottom), (top + bottom) / (top - bottom),   0                             },
      {0,                         0,                         -(far + near) / (far - near),      -2 * far * near / (far - near)},
      {0,                         0,                         -1,                                0                             }
    });
  }
  
  template<typename T>
  inline Mat<4, 4, T> perspective(T fov_y, T aspect, T near, T far)
  {
    const T t = math::tan(fov_y / 2);
    return Mat<4, 4, T>({
      {1 / (aspect * t), 0,     0,                            0                             },
      {0,                1 / t, 0,                            0                             },
      {0,                0,     -(far + near) / (far - near), -2 * far * near / (far - near)},
      {0,                0,     1,                            0                             }
    });
  }

  template<typename T>
  inline bool check_affine(const Mat<3, 3, T>& rhs)
  {
    return (rhs[2][0] == 0 && rhs[2][1] == 0 && rhs[2][2] == 1);
  }

  template<typename T>
  inline bool check_affine(const Mat<4, 4, T>& rhs)
  {
    return (rhs[3][0] == 0 && rhs[3][1] == 0 && rhs[3][2] == 0 && rhs[3][3] == 1);
  }

#pragma endregion
}