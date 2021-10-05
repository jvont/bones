#pragma once

#include <core/string/str.h>
#include <core/time/time.h>

#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>

// TODO: add header/footer, append to existing log file (based on footer)

#define PROFILER_ENABLED

#ifdef PROFILER_ENABLED
  // get function signature (based on compiler)
  // from: https://stackoverflow.com/questions/27174929/what-is-a-best-way-to-check-if-compiler-supports-func-etc
  #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))
    # define _FUNC_NAME_ __PRETTY_FUNCTION__
  #elif defined(__DMC__) && (__DMC__ >= 0x810)
    # define _FUNC_NAME_ __PRETTY_FUNCTION__
  #elif defined(__FUNCSIG__)
    # define _FUNC_NAME_ __FUNCSIG__
  #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
    # define _FUNC_NAME_ __FUNCTION__
  #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
    # define _FUNC_NAME_ __FUNC__
  #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    # define _FUNC_NAME_ __func__
  #else
    # define _FUNC_NAME_ "function identifier unknown"
  #endif

  #define _PROFILE_SCOPE_(name, line) bones::ProfilerSession session##__LINE__(name)

  #define PROFILER_OPEN(path)         bones::Profiler::get_instance().open(path)
  #define PROFILER_CLOSE()            bones::Profiler::get_instance().close()

  #define PROFILE_BEGIN(name)         bones::Profiler::get_instance().begin_session(name)
  #define PROFILE_END(name)           bones::Profiler::get_instance().end_session(name)
  #define PROFILE_SCOPE(name)         _PROFILE_SCOPE_(name, __LINE__)
  #define PROFILE_FUNC()              PROFILE_SCOPE(_FUNC_NAME_)
#else
  #define PROFILER_OPEN(path)
  #define PROFILER_CLOSE()

  #define PROFILE_BEGIN(name)
  #define PROFILE_END(name)
  #define PROFILE_SCOPE(name)         
  #define PROFILE_FUNC()
#endif

namespace bones
{
  class Profiler
  {
    using TimePoint = std::chrono::high_resolution_clock::time_point;

  public:
    static Profiler& get_instance()
    {
      static Profiler instance;
      return instance;
    }

  private:
    Profiler() = default;
    
    Str path;
    bool is_open;
    std::ostringstream oss;

    std::map<Str, TimePoint> sessions;
    std::mutex mutex;

  public:
    Profiler(const Profiler&) = delete;
    void operator=(const Profiler&) = delete;
    ~Profiler();

    void open(const Str& path);
    void close();

    void begin_session(const Str& name);
    void end_session(const Str& name);
  };

  // simple wrapper used for scoped sessions
  class ProfilerSession
  {
  private:
    Str name;

  public:
    ProfilerSession(const Str& name);
    ~ProfilerSession();
  };
}