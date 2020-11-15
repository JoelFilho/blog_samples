#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace jf {

namespace detail {
template <std::size_t Length, typename Generator, std::size_t... Indexes>
constexpr auto lut_impl(Generator&& f, std::index_sequence<Indexes...>) {
  using content_type = decltype(f(std::size_t{0}));
  return std::array<content_type, Length>{{f(Indexes)...}};
}
}  // namespace detail

template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  return detail::lut_impl<Length>(std::forward<Generator>(f), std::make_index_sequence<Length>{});
}

}  // namespace jf