#include <core/debug/log.h>
#include <resources/image.h>
#include <resources/texture.h>

#include <glad/glad.h>

namespace bones
{
  Texture::Texture()
    : id(0)
  {}

  Texture::Texture(const Str& path)
  {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // texture wrapping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    Image img(path);
    GLint format;
    switch (img.format)
    {
      // case Image::FORMAT_G:
      //   break;
      // case Image::FORMAT_GA:
      //   break;
      case Image::FORMAT_RGB:
        format = GL_RGB;
        break;
      case Image::FORMAT_RGBA:
        format = GL_RGBA;
        break;
      case Image::FORMAT_NONE:
      default:
        logerror << "error loading image: format " << img.format << "not supported" << logendl;
        return;
    };

    glTexImage2D(GL_TEXTURE_2D, 0, format, img.width, img.height, 0, format, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &id);
  }

  Texture::Texture(Texture&& texture)
    : id(texture.id)
  {
    texture.id = 0;
  }

  Texture& Texture::operator=(Texture&& rhs)
  {
    glDeleteTextures(1, &id);
    id = rhs.id;
    rhs.id = 0;
    return *this;
  }

  void Texture::bind()
  {
    glBindTexture(GL_TEXTURE_2D, id);
  }

  void Texture::from_file(const Str& path)
  {
    // Image* img = Image::from_file(path);
    // if (img == nullptr)
    // {
    //   logerror << "Failed to load texture" << logendl;
    //   return nullptr;
    // }

    // unsigned int format;
    // switch (img->format)
    // {
    //   case ImageFormat::RGB:
    //     format = GL_RGB;
    //     break;
    //   case ImageFormat::RGBA:
    //     format = GL_RGBA;
    //     break;
    //   default:
    //     logerror << "Image format not supported" << logendl;
    //     return new Texture(0);
    // }
    // glTexImage2D(GL_TEXTURE_2D, 0, format, img->width, img->height, 0, format, GL_UNSIGNED_BYTE, img->data);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // delete img;
  }
}