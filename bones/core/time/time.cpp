#include <core/time/time.h>

#include <chrono>
#include <ctime>
#include <mutex>
#include <thread>
using namespace std::chrono;

namespace
{
  steady_clock::time_point steady_start = steady_clock::now();
}

namespace bones
{
  TimeInfo::TimeInfo(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second)
  {}

  Str TimeInfo::isoformat(const Str& sep)
  {
    return format_s("%04d-%02d-%02d%s%02d:%02d:%02d", year, month, day, sep, hour, minute, second);
  }

  u64 time::millis()
  {
    return duration_cast<milliseconds>(steady_clock::now() - steady_start).count();
  }

  u64 time::micros()
  {
    return duration_cast<microseconds>(steady_clock::now() - steady_start).count();
  }

  u64 time::nanos()
  {
    return duration_cast<nanoseconds>(steady_clock::now() - steady_start).count();
  }

  void time::sleep(int millis)
  {
    if (millis > 0)
      std::this_thread::sleep_for(milliseconds(millis));
  }

  TimeInfo time::local_time()
  {
    system_clock::time_point now = system_clock::now();
    time_t now_tt = system_clock::to_time_t(now);
    tm local_tm;
#if defined(__unix__)
    localtime_r(&now_tt, &local_tm);
#elif defined(_MSC_VER)
    localtime_s(&local_tm, &now_tt);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    local_tm = *std::localtime(&now_tt);
#endif

    return TimeInfo(
      local_tm.tm_year + 1900,
      local_tm.tm_mon,
      local_tm.tm_mday,
      local_tm.tm_hour,
      local_tm.tm_min,
      local_tm.tm_sec
    );
  }

  TimeInfo time::utc_time()
  {
    system_clock::time_point now = system_clock::now();
    time_t now_tt = system_clock::to_time_t(now);
    tm utc_tm;
#if defined(__unix__)
    gmtime_r(&now_tt, &utc_tm);
#elif defined(_MSC_VER)
    gmtime_s(&utc_tm, &now_tt);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    utc_tm = *std::gmtime(&now_tt);
#endif

    return TimeInfo(
      utc_tm.tm_year + 1900,
      utc_tm.tm_mon,
      utc_tm.tm_mday,
      utc_tm.tm_hour,
      utc_tm.tm_min,
      utc_tm.tm_sec
    );
  }
}