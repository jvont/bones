#pragma once

#include <core/math/color/color.h>
#include <core/math/spatial/mat.h>
#include <core/math/spatial/vec.h>
#include <core/string/str.h>

#include <map>

namespace bones
{
  // TODO: hot-reloading, check for file modifications

  enum class ShaderType
  {
    Float,
    Int,
    Vec2,
    Vec3,
    Vec4,
    Mat2,
    Mat3,
    Mat4,
    Sampler2D
  };

  struct AttributeInfo
  {
    unsigned int loc;
    int size;
    ShaderType type;
  };

  struct UniformInfo
  {
    unsigned int loc;
    int size;
    ShaderType type;
  };

  class Shader
  {
  private:
    Str vs_path, fs_path;
    unsigned int id;

    // std::vector<VertexAttribute> attributes;
    // std::vector<Uniform> uniforms;

    std::map<Str, AttributeInfo> attributes;
    std::map<Str, UniformInfo> uniforms;

    // obtain relevant attribute info for attribpointer
    // route uniform info for setters

  public:
    Shader();
    Shader(const Str& vs_path, const Str& fs_path);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    
    Shader(Shader&& shader);
    Shader& operator=(Shader&& rhs);

    // void load(const Str& vs_path, const Str& fs_path);
    // void reload();

    void use();

    void set_uniform(const Str& name, float value);
    void set_uniform(const Str& name, int value);

    void set_uniform(const Str& name, const Vec2& value);
    void set_uniform(const Str& name, const Vec3& value);
    void set_uniform(const Str& name, const Vec4& value);

    void set_uniform(const Str& name, const Mat2& value);
    void set_uniform(const Str& name, const Mat3& value);
    void set_uniform(const Str& name, const Mat4& value);

    void set_uniform(const Str& name, const float values[], int size);
    void set_uniform(const Str& name, const Vec2 values[], int size);
    void set_uniform(const Str& name, const Vec3 values[], int size);
    void set_uniform(const Str& name, const Vec4 values[], int size);

    void set_uniform(const Str& name, const Color& value);
  };
}