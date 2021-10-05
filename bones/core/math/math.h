#pragma once

#include <cfloat>
#include <cmath>

// math constants
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

#ifndef M_TAU
  #define M_TAU 6.28318530717958647693
#endif

#ifndef M_E
  #define M_E   2.71828182845904523536
#endif

// machine constants
#ifndef FLT_EPSILON
  #define FLT_EPSILON 1.192092896e-07F
#endif

#ifndef DBL_EPSILON
  #define DBL_EPSILON 2.2204460492503131e-016
#endif

namespace bones
{
  namespace math
  {
    // namespace constants
    constexpr double pi =  3.14159265358979323846;
    constexpr double tau = 6.28318530717958647693;
    constexpr double e =   2.71828182845904523536;

    // template methods
    template<typename T>
    inline T pow(T b, T e) { return static_cast<T>(::pow(b, e)); }

    template<typename T>
    inline T max(T a, T b) { return ((a > b) ? a : b); }

    template<typename T>
    inline T min(T a, T b) { return ((a < b) ? a : b); }

    template<typename T>
    inline T sgn(T a) { return ((a >= 0) ? 1 : -1); }

    template<typename T>
    inline T abs(T a) { return ((a >= 0) ? a : -a); }

    // NOTE: any max/min overrides should comply with this method
    template<typename T>
    inline T clamp(T x, T a, T b) { return max(a, min(x, b)); }
    
    template<typename T>
    inline T lerp(const T& a, const T& b, double t) { return static_cast<T>(a + (b - a) * t); }

    template<typename T>
    inline T lerp(const T& a, const T& b, float t) { return static_cast<T>(a + (b - a) * t); }

    template<typename T>
    inline T lerp_clamp(const T& a, const T& b, double t) { return lerp(a, b, clamp(t, 0.0, 1.0)); }

    template<typename T>
    inline T lerp_clamp(const T& a, const T& b, float t) { return lerp(a, b, clamp(t, 0.0f, 1.0f)); }

    // floating-point methods
    inline bool approx_equal(float a, float b, float tol = FLT_EPSILON) { return abs(a - b) <= (tol * max(1.0f, max(a, b))); }
    inline bool approx_equal(double a, double b, double tol = DBL_EPSILON) { return abs(a - b) <= (tol * max(1.0, max(a, b))); }

    inline float sqrt(float x) { return ::sqrt(x); }
    inline double sqrt(double x) { return ::sqrt(x); }

    inline float ceil(float x) { return ::ceil(x); }
    inline double ceil(double x) { return ::ceil(x); }

    inline float floor(float x) { return ::floor(x); }
    inline double floor(double x) { return ::floor(x); }

    inline float round(float x) { return ::round(x); }
    inline double round(double x) { return ::round(x); }

    inline float log(float x) { return ::log(x); }
    inline double log(double x) { return ::log(x); }

    inline float log10(float x) { return ::log10(x); }
    inline double log10(double x) { return ::log10(x); }

    inline float exp(float x) { return ::exp(x); }
    inline double exp(double x) { return ::exp(x); }

    // Quake III's fast inverse square root algorithm (for funsies)
    inline float fast_inv_sqrt(float x)
    {
      long i;
      float x2, y;
      const float threehalfs = 1.5f;

      x2 = x * 0.5F;
      y = x;
      i = * (long*) &y;                     // evil floating point bit level hacking
      i = 0x5f3759df - (i >> 1);            // what the fuck? 
      y = * (float*) &i;
      y = y * (threehalfs - (x2 * y * y));  // 1st iteration
      // y  = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed
      return y;
    }

    // trigonometry
    inline float sin(float x) { return ::sin(x); }
    inline double sin(double x) { return ::sin(x); }

    inline float cos(float x) { return ::cos(x); }
    inline double cos(double x) { return ::cos(x); }

    inline float tan(float x) { return ::tan(x); }
    inline double tan(double x) { return ::tan(x); }

    inline float asin(float x) { return ::asin(x); }
    inline double asin(double x) { return ::asin(x); }

    inline float acos(float x) { return ::acos(x); }
    inline double acos(double x) { return ::acos(x); }

    inline float atan(float x) { return ::atan(x); }
    inline double atan(double x) { return ::atan(x); }

    inline float atan2(float y, float x) { return ::atan2(y, x); }
    inline double atan2(double y, double x) { return ::atan2(y, x); }

    inline float to_deg(float rad) { return (rad * (float)(180.0 / M_PI)); }
    inline double to_deg(double rad) { return (rad * 180.0 / M_PI); }

    inline float to_rad(float deg) { return (deg * (float)(M_PI / 180.0)); }
    inline double to_rad(double deg) { return (deg * M_PI / 180.0); }
  }
}