#pragma once

#include <memory>
#include <string>
#include <utility>

namespace bones
{
  using Str = std::string;

  // format functions from: https://gist.github.com/Zitrax/a2e0040d301bf4b8ef8101c0b1e3f1d5

  // convert std::string to const char*
  template<typename Arg>
  auto convert_s(Arg&& arg)
  {
    if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<Arg>>, Str>::value)
      return std::forward<Arg>(arg).c_str();
    else
      return std::forward<Arg>(arg);
  }

  // format string using format specifiers (s, internal)
  template<typename ... Args>
  Str _format_s_impl_(const Str& format, Args&& ... args)
  {
    size_t size = snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...) + 1;
    if( size <= 0 ) { throw std::runtime_error("Error during formatting."); }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return Str(buf.get(), buf.get() + size - 1);
  }

  // format string using format specifiers
  template<typename ... Args>
  Str format_s(const Str& format, Args&& ... args)
  {
    return _format_s_impl_(format, convert_s(std::forward<Args>(args))...);
  }

  // format string using replacement fields (C++20)
  // template<typename ...Args>
  // Str format_f(const Str& format, Args&&... args)
  // {
  //   return std::format(format, args...);
  // }
}