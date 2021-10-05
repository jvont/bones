#include <core/debug/log.h>
#include <core/debug/profiler.h>

#include <fstream>
#include <iomanip>

namespace bones
{
  void Profiler::open(const Str& path)
  {
    if (is_open)
      logerror << "Log instance is already open at " << this->path << logendl;
    
    is_open = true;
    this->path = path;
  }

  void Profiler::close()
  {
    if (is_open)
    {
      std::lock_guard lock(mutex);
      std::ofstream ofs;
      ofs.open(path);
      if (ofs.is_open())
      {
        ofs << oss.str();
        ofs.close();
      }
    }
    oss.clear();
    is_open = false;
  }

  Profiler::~Profiler()
  {
    close();
  }

  void Profiler::begin_session(const Str& name)
  {
    std::lock_guard lock(mutex);
    if (sessions.count(name))
    {
      logerror << "Session with name '" << name << "' is already open." << logendl;
    }
    else
    {
      sessions[name] = std::chrono::high_resolution_clock::now();
    }
  }

  void Profiler::end_session(const Str& name)
  {
    std::lock_guard lock(mutex);
    if (sessions.count(name))
    {
      TimePoint now = std::chrono::high_resolution_clock::now();
      double dt = std::chrono::duration_cast<std::chrono::microseconds>(now - sessions[name]).count() / 1e6;
      if (is_open)
        oss << name << ',' << std::setprecision(6) << std::fixed << dt << '\n';
      sessions.erase(name);
    }
    else
    {
      logerror << "Session with name '" << name << "' does not exist." << logendl;
    }
  }

  ProfilerSession::ProfilerSession(const Str& name)
    : name(name)
  {
    Profiler::get_instance().begin_session(name);
  }

  ProfilerSession::~ProfilerSession()
  {
    Profiler::get_instance().end_session(name);
  }
}