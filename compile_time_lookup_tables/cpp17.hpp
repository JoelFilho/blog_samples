#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace jf {

// C++17 LUT generation
// std::array is now fully constexpr, so we can just create it in time
// Issue: requires constexpr default-constructible and copy-constructible types
template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  // Create the return array, with default-constructed content
  // content_type may also be declared as std::invoke_result_t<Generator, std::size_t>
  using content_type = decltype(f(std::size_t{0}));
  std::array<content_type, Length> arr{};

  // Fill the array, using a for loop
  for (std::size_t i = 0; i < Length; i++) {
    // Directly calling f(i), as C++17's std::invoke is not constexpr, only on C++20
    arr[i] = f(i);
  }

  // Return
  return arr;
}

}  // namespace jf