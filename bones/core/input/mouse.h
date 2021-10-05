#pragma once

#include <core/typedefs.h>

namespace bones
{
  enum class MouseButton : u8
	{
		None   = (0 << 0),
		Left   = (1 << 0),
		Middle = (1 << 1),
		Right  = (1 << 2),
    X1     = (1 << 3),
    X2     = (1 << 4)
	};

  // add bitwise operator overloading
}