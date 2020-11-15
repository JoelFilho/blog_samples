#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace jf {

namespace detail {
template <std::size_t Length, typename T, typename Generator, typename... Values>
constexpr auto lut_impl(Generator&& f, Values... values) 
  -> typename std::enable_if<sizeof...(Values) == (Length - 1), std::array<T, Length>>::type {
  return {values..., std::forward<Generator>(f)(sizeof...(Values))};
}

template <std::size_t Length, typename T, typename Generator, typename... Values>
constexpr auto lut_impl(Generator&& f, Values... values)
  -> typename std::enable_if<sizeof...(Values) < (Length - 1), std::array<T, Length>>::type {
  return lut_impl<Length, T, Generator, Values..., decltype(f(std::size_t{0}))>(
	  std::forward<Generator>(f),
	  values...,
	  f(sizeof...(Values)));
}
}  // namespace detail


template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f)
    -> std::array<decltype(f(std::size_t{0})), Length> {
  return detail::lut_impl<Length, decltype(f(std::size_t{0}))>(std::forward<Generator>(f));
}

}  // namespace jf