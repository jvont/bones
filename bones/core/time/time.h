#pragma once

#include <core/string/str.h>
#include <core/typedefs.h>

namespace bones
{
  struct TimeInfo
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    TimeInfo(int year, int month, int day, int hour, int minute, int second);
    Str isoformat(const Str& sep = " ");
  };

  namespace time
  {
    u64 millis();
    u64 micros();
    u64 nanos();

    void sleep(int millis);

    TimeInfo local_time();
    TimeInfo utc_time();
  }
}