#include <core/debug/log.h>
#include <core/time/time.h>

#include <fstream>

namespace bones
{
  void Log::open(const Str& path)
  {
    if (is_open)
      logerror << "Log instance is already open at " << this->path << logendl;
    
    is_open = true;
    this->path = path;
  }

  void Log::close()
  {
    std::lock_guard lock(mutex);
    if (is_open)
    {
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

  Log::~Log()
  {
    close();
  }

  Str Log::color(const Color& c)
  {
    // from: https://stackoverflow.com/a/62788770/15837840
    // format: "\033[38;2;R;G;Bm"
    std::cout << "\033[38;2;" << (int)(c.r * 255.999f) << ";"
                              << (int)(c.g * 255.999f) << ";"
                              << (int)(c.b * 255.999f) << "m";
    return "";
  }

  Str Log::background(const Color& c)
  {
    // format: "\033[48;2;R;G;Bm"
    std::cout << "\033[48;2;" << (int)(c.r * 255.999f) << ";"
                              << (int)(c.g * 255.999f) << ";"
                              << (int)(c.b * 255.999f) << "m";
    return "";
  }

  Str Log::reset()
  {
    std::cout << "\u001b[0m";
    return "";
  }

  Str Log::get_time()
  {
    return time::local_time().isoformat();
  }
}