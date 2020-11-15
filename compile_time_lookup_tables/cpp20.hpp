#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <utility>

namespace jf {

template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  // The return array
  using content_type = decltype(f(std::size_t{0}));
  std::array<content_type, Length> arr;

  // Process using ranges and copy to our array
  using namespace std::ranges;
  auto rangy = views::iota(std::size_t{0}, Length)            // Generate a sequence
             | views::transform(std::forward<Generator>(f));  // Transform using our generator
  copy(rangy, arr.begin());

  // Return
  return arr;
}

}  // namespace jf