#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace jf {

namespace detail {

// End of recursive implementation: create the array
template <std::size_t Length, typename T, typename Generator, typename... Values>
constexpr auto lut_impl(Generator&& f, Values... values)
  -> typename std::enable_if<sizeof...(Values) == (Length - 1), std::array<T, Length>>::type
{
  return {values..., std::forward<Generator>(f)(sizeof...(Values))};
}

// Recursive implementation of the LUT creation: append the current values to the function call's argument list
template <std::size_t Length, typename T, typename Generator, typename... Values>
constexpr auto lut_impl(Generator&& f, Values... values)
  -> typename std::enable_if<sizeof...(Values) < (Length - 1), std::array<T, Length>>::type
{
  return lut_impl<Length, T>(std::forward<Generator>(f), values..., f(sizeof...(Values)));
}

}  // namespace detail


// LUT creation in C++11: we define the array content type, then call our implementation
template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f)
  -> std::array<decltype(f(std::size_t{0})), Length>
{
  // Update: content_type may also be defined as
  // typename std::result_of<Generator(std::size_t)>::type
  using content_type = decltype(f(std::size_t{0}));
  return detail::lut_impl<Length, content_type>(std::forward<Generator>(f));
}

}  // namespace jf