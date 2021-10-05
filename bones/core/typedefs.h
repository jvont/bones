#pragma once

#include <cstdint>
#include <functional>
#include <memory>

namespace bones
{
  // signed integers
  using i8 = int8_t;
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  
  // unsigned integers
  using u8 = uint8_t;
  using u16 = uint16_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  using byte = uint8_t;
  using word = uint16_t;
  using dword = uint32_t;

  // floating-point numbers
  using f32 = float;
  using f64 = double;

  template <typename R, typename... Args>
  using Function = std::function<R(Args...)>;
  // using Function = R(*)(Args...);

  template <typename... Args>
  using Callback = std::function<void(Args...)>;
  // using Callback = void(*)(Args...);

  // shared references
  template<typename T>
	using Ref = std::shared_ptr<T>;

  template<typename T, typename... Args>
  Ref<T> create_ref(Args... args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}