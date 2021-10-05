#pragma once

#include <core/math/color/color.h>
#include <core/string/str.h>

#include <iostream>
#include <mutex>
#include <sstream>
#include <utility>

// idea from: https://levelup.gitconnected.com/logging-in-c-60cd1571df15

// TODO: add header/footer, append to existing log file (based on footer)
// TODO: add callbacks for error/warning/debug messages

#define LOG_ENABLED

#ifdef LOG_ENABLED
  #define _LOG_FG_(c)   bones::Log::get_instance().color(c)
  #define _LOG_BG_(c)   bones::Log::get_instance().background(c)
  #define _LOG_RESET_   bones::Log::get_instance().reset()
  #define _LOG_TIME_    bones::Log::get_instance().get_time()

  #define _LOG_OUT_     bones::Log::get_instance() << _LOG_RESET_ << _LOG_FG_(bones::Color::dodger_blue) << _LOG_TIME_ << _LOG_RESET_ << " "
  #define _LOG_TRACE_   _LOG_FG_(bones::Color::dodger_blue) << __FILE__ << "(" << __LINE__ << "):" << _LOG_RESET_ << " "

  #define logopen(path) bones::Log::get_instance().open(path)
  #define logclose()    bones::Log::get_instance().close()

  #define loginfo       _LOG_OUT_ << _LOG_FG_(bones::Color::blue)   << _LOG_BG_(bones::Color::light_gray) << "INFO " << _LOG_RESET_ << " "
  #define logwarn       _LOG_OUT_ << _LOG_FG_(bones::Color::yellow) << _LOG_BG_(bones::Color::light_gray) << "WARN " << _LOG_RESET_ << " " << _LOG_TRACE_
  #define logerror      _LOG_OUT_ << _LOG_FG_(bones::Color::red)    << _LOG_BG_(bones::Color::light_gray) << "ERROR" << _LOG_RESET_ << " " << _LOG_TRACE_
  #define logendl       '\n'
#else
  #define logopen(path) 
  #define logclose()    

  #define loginfo       bones::NullLog::get_instance()
  #define logwarn       bones::NullLog::get_instance()
  #define logerror      bones::NullLog::get_instance()
  #define logendl       '\0'
#endif

namespace bones
{
  // c++11 singleton implmenetation from:
  // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

  class Log
  {
  public:
    static Log& get_instance()
    {
      static Log instance;
      return instance;
    }

  private:
    Log() = default;
    
    Str path;
    bool is_open;
    std::ostringstream oss;

    std::mutex mutex;

  public:
    ~Log();
    Log(const Log&) = delete;
    void operator=(const Log&) = delete;

    void open(const Str& path);
    void close();

    Str color(const Color& c);
    Str background(const Color& c);
    Str reset();

    static Str get_time();

    template<typename T> Log& operator<<(T rhs)
    {
      std::lock_guard lock(mutex);
      std::cout << rhs;
      if (is_open)
        oss << rhs;
      return *this;
    }

    // Log& operator<<(std::ostream& (*fun)(std::ostream&))
    // {
    //   std::lock_guard lock(mutex);
    //   std::cout << fun;
    //   if (is_open)
    //     oss << fun;
    //   return *this;
    // }
  };

  class NullLog
  {
  public:
    static NullLog& get_instance()
    {
      static NullLog instance;
      return instance;
    }

  private:
    NullLog() = default;

  public:
    ~NullLog() = default;
    NullLog(const NullLog&) = delete;
    void operator=(const NullLog&) = delete;

    template<typename T> NullLog& operator<<(T rhs)
    {
      return *this;
    }
  };
}