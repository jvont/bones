#pragma once

#include <core/string/str.h>

namespace bones
{
  class Texture
  {
  private:
    unsigned int id;
    
  public:
    Texture();
    Texture(const Str& path);
    ~Texture();

    Texture(const Texture& texture) = delete;
    Texture& operator=(const Texture&) = delete;
    
    Texture(Texture&& texture);
    Texture& operator=(Texture&& rhs);

    void bind();
    
    void from_file(const Str& path);
  };
}