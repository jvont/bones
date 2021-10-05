#pragma once

namespace bones
{
  class Image
  {
  public:
    enum Format
    {
      FORMAT_NONE = 0,
      // FORMAT_G = 1,
      // FORMAT_GA = 2,
      FORMAT_RGB = 3,
      FORMAT_RGBA = 4
    };
  
  private:
    int width, height;
    Format format;
    unsigned char* data;
    
  public:
    Image();
    Image(const Str& path, bool flip_y = true);
    Image(int width, int height, Format format, unsigned char* data = nullptr);
    ~Image();

    Image(const Image& image);
    Image& operator=(const Image&);
    
    Image(Image&& image);
    Image& operator=(Image&& rhs);
    
    // static Image* from_source(unsigned char* data);

    // TODO: set required image format, return null otherwise
    // static Image from_file(const Str& path, bool flip_y = true);

    friend class Texture;
  };

  // TODO: free template function 'open()' for loading files (images, ttf, audio, etc.)
}