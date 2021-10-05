#include <core/debug/log.h>
#include <resources/image.h>

#include <stb_image.h>

#include <string.h>

namespace bones
{
  Image::Image()
    : width(0), height(0), format(FORMAT_NONE), data(nullptr)
  {}

  Image::Image(const Str& path, bool flip_y)
  {
    int components;
    stbi_set_flip_vertically_on_load(flip_y);
    data = stbi_load(path.c_str(), &width, &height, &components, 0);
    if (data == nullptr)
    {
      logerror << "Could not load image at " << path << logendl;
      return;
    }

    switch (components)
    {
      // case STBI_grey:
      //   break;
      // case STBI_grey_alpha:
      //   break;
      case STBI_rgb:
        format = FORMAT_RGB;
        break;
      case STBI_rgb_alpha:
        format = FORMAT_RGBA;
        break;
      default:
        format = FORMAT_NONE;
        logerror << "stb_image format not supported: " << components << logendl;
        stbi_image_free(data);
        break;
    }
  }

  Image::Image(int width, int height, Format format, unsigned char* data)
    : width(width), height(height), format(format), data(data)
  {}

  Image::~Image()
  {
    stbi_image_free(data);
  }

  Image::Image(const Image& image)
    : width(image.width), height(image.height), format(image.format)
  {
    if (image.data == nullptr)
    {
      logwarn << "copy constructor: image data is null" << logendl;
    }
    else
    {
      std::size_t size = width * height * format;
      data = (unsigned char*)malloc(size);
      memcpy(data, image.data, size);
    }
  }

  Image& Image::operator=(const Image& rhs)
  {
    width = rhs.width;
    height = rhs.height;
    format = rhs.format;

    stbi_image_free(data);
    if (rhs.data == nullptr)
    {
      logwarn << "copy assignment: image data is null" << logendl;
    }
    else
    {
      std::size_t size = width * height * format;
      data = (unsigned char*)malloc(size);
      memcpy(data, rhs.data, size);
    }
    return *this;
  }

  Image::Image(Image&& image)
    : width(image.width), height(image.height), format(image.format), data(image.data)
  {
    image.data = nullptr;
  }

  Image& Image::operator=(Image&& rhs)
  {
    width = rhs.width;
    height = rhs.height;
    format = rhs.format;

    stbi_image_free(data);
    data = rhs.data;
    rhs.data = nullptr;
    return *this;
  }
}