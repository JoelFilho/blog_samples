#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <utility>

namespace jf {

template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  // The return array, with default-constructed content
  // content_type may also be declared as std::invoke_result_t<Generator, std::size_t>
  using content_type = decltype(f(std::size_t{0}));
  std::array<content_type, Length> arr;

  // Create a view range that will lazily evaluate our function for each array position
  using namespace std::ranges;
  auto range = views::iota(std::size_t{0}, Length)            // Generate the interval [0, Length-1]
             | views::transform(std::forward<Generator>(f));  // Transform using our generator

  // Copy our range to our array, using constexpr range-based algorithms
  copy(range, arr.begin());

  // Return
  return arr;
}

}  // namespace jf