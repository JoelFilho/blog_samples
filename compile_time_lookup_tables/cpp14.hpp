#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace jf {

namespace detail {

// Implementation: construct all array items in the array using pack expansion
template <std::size_t Length, typename Generator, std::size_t... Indexes>
constexpr auto lut_impl(Generator&& f, std::index_sequence<Indexes...>) {
  // Update: content_type may also be defined as
  // std::result_of_t<Generator(std::size_t)>
  using content_type = decltype(f(std::size_t{0}));
  return std::array<content_type, Length>{{f(Indexes)...}};
}

}  // namespace detail

// C++14 version, using the std::index_sequence utility
// We create the index sequence, which forwards the [0, Length-1] interval to the implementation
template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  return detail::lut_impl<Length>(std::forward<Generator>(f), std::make_index_sequence<Length>{});
}

}  // namespace jf