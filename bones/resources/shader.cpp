#include <core/debug/log.h>
#include <resources/shader.h>

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace
{
  std::map<GLenum, bones::ShaderType> type_map = {
    {GL_FLOAT, bones::ShaderType::Float},
    {GL_INT, bones::ShaderType::Int},
    {GL_FLOAT_VEC2, bones::ShaderType::Vec2},
    {GL_FLOAT_VEC3, bones::ShaderType::Vec3},
    {GL_FLOAT_VEC4, bones::ShaderType::Vec4},
    {GL_FLOAT_MAT2, bones::ShaderType::Mat2},
    {GL_FLOAT_MAT3, bones::ShaderType::Mat3},
    {GL_FLOAT_MAT4, bones::ShaderType::Mat4},
    {GL_SAMPLER_2D, bones::ShaderType::Sampler2D}
  };

  bones::Str load_shader_file(const bones::Str& path)
  {
    std::string output;
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      ifs.open(path);
      std::ostringstream oss;
      oss << ifs.rdbuf();
      ifs.close();
      output = oss.str();
    }
    catch(std::ifstream::failure e)
    {
      logerror << "Shader file not succesfully read" << logendl;
    }
    return output;
  }

  unsigned int compile_shader(const bones::Str& code, GLenum shader_type)
  {
    const char* c_str = code.c_str();
    unsigned int id = glCreateShader(shader_type);
    glShaderSource(id, 1, &c_str, NULL);
    glCompileShader(id);

    int status;
    char info_log[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
      glGetShaderInfoLog(id, 1024, NULL, info_log);
      logerror << info_log << logendl;
    }
    return id;
  }
}

namespace bones
{
  Shader::Shader()
    : id(0)
  {}

  Shader::Shader(const Str& vs_path, const Str& fs_path)
    : vs_path(vs_path), fs_path(fs_path)
  {
    // load shaders
    Str vs_code = load_shader_file(vs_path);
    Str fs_code = load_shader_file(fs_path);

    // create/compile shaders
    unsigned int vs_id = compile_shader(vs_code.c_str(), GL_VERTEX_SHADER);
    unsigned int fs_id = compile_shader(fs_code.c_str(), GL_FRAGMENT_SHADER);

    // create shader program and link shaders
    id = glCreateProgram();
    glAttachShader(id, vs_id);
    glAttachShader(id, fs_id);
    glLinkProgram(id);

    int status;
    char info_log[1024];
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status)
    {
      glGetProgramInfoLog(id, 1024, NULL, info_log);
      logerror << info_log << logendl;
    }

    // delete shaders after linking
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    // save active attribute info
    char buf[128];
    GLint count;
    GLenum gl_type;
    glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &count);
    for (GLint i = 0; i < count; i++)
    {
      AttributeInfo info;
      glGetActiveAttrib(id, i, sizeof(buf), 0, &info.size, &gl_type, buf);
      info.loc = glGetAttribLocation(id, buf);
      if (!type_map.count(gl_type))
      {
        logerror << "attribute type " << gl_type << " not supported by shader class" << logendl;
        continue;
      }
      info.type = type_map[gl_type];
      attributes[Str(buf)] = info;
    }
    
    // save active uniform info
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);
    for (GLint i = 0; i < count; i++)
    {
      UniformInfo info;
      glGetActiveUniform(id, i, sizeof(buf), 0, &info.size, &gl_type, buf);
      info.loc = glGetUniformLocation(id, buf);
      if (!type_map.count(gl_type))
      {
        logerror << "uniform type " << gl_type << " not supported by shader class" << logendl;
        continue;
      }
      info.type = type_map[gl_type];
      uniforms[Str(buf)] = info;
    }
  }

  Shader::~Shader()
  {
    glDeleteProgram(id);
  }

  Shader::Shader(Shader&& shader)
    : id(shader.id),
      vs_path(shader.vs_path), fs_path(shader.fs_path),
      attributes(shader.attributes), uniforms(shader.uniforms)
  {
    shader.id = 0;
  }

  Shader& Shader::operator=(Shader&& rhs)
  {
    id = rhs.id;
    vs_path = rhs.vs_path;
    fs_path = rhs.fs_path;
    attributes = rhs.attributes;
    uniforms = rhs.uniforms;
    rhs.id = 0;
    return *this;
  }

  // void Shader::load(const Str& vs_path, const Str& fs_path)
  // {

  // }

  // void Shader::reload()
  // {

  // }

  void Shader::use()
  {
    glUseProgram(id);
  }

  void Shader::set_uniform(const Str& name, float value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Float);
    glUniform1f(info.loc, value);
  }

  void Shader::set_uniform(const Str& name, int value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Int || info.type == ShaderType::Sampler2D);
    glUniform1i(info.loc, value);
  }

  void Shader::set_uniform(const Str& name, const Vec2& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec2);
    glUniform2f(info.loc, value.x, value.y);
  }

  void Shader::set_uniform(const Str& name, const Vec3& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec3);
    glUniform3f(info.loc, value.x, value.y, value.z);
  }

  void Shader::set_uniform(const Str& name, const Vec4& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec4);
    glUniform4f(info.loc, value.x, value.y, value.z, value.w);
  }

  void Shader::set_uniform(const Str& name, const Mat2& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Mat2);
    glUniformMatrix2fv(uniforms[name].loc, 1, GL_FALSE, &value[0][0]);
  }

  void Shader::set_uniform(const Str& name, const Mat3& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Mat3);
    glUniformMatrix3fv(uniforms[name].loc, 1, GL_FALSE, &value[0][0]);
  }

  void Shader::set_uniform(const Str& name, const Mat4& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Mat4);
    glUniformMatrix4fv(info.loc, 1, GL_FALSE, &value[0][0]);
  }

  void Shader::set_uniform(const Str& name, const float values[], int size)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Float && info.size == size);
    glUniform1fv(info.loc, size, (float *)(&values[0]));
  }

  void Shader::set_uniform(const Str& name, const Vec2 values[], int size)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec2 && info.size == size);
    glUniform2fv(uniforms[name].loc, size, (float *)(&values[0][0]));
  }

  void Shader::set_uniform(const Str& name, const Vec3 values[], int size)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec3 && info.size == size);
    glUniform3fv(uniforms[name].loc, size, (float *)(&values[0][0]));
  }

  void Shader::set_uniform(const Str& name, const Vec4 values[], int size)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec4 && info.size == size);
    glUniform4fv(uniforms[name].loc, size, (float *)(&values[0][0]));
  }

  void Shader::set_uniform(const Str& name, const Color& value)
  {
    assert(uniforms.count(name));
    UniformInfo &info = uniforms[name];
    assert(info.type == ShaderType::Vec4);
    glUniform4f(info.loc, value.r, value.g, value.b, value.a);
  }
}