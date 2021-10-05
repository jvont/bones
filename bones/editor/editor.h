#pragma once

namespace bones
{
  class Editor
  {
  protected:

  public:
    Editor() = default;
    ~Editor() = default;

    virtual void render() = 0;
  };
}