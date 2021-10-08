//
// Created by georgios on 08.10.21.
//

#ifndef CPPBUFFER_STBUFFER_HPP
#define CPPBUFFER_STBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace mpsh {
namespace detail {
// calculate the partial sum of Nelem elements of the given types
// we should make sure that all these types are of the same (numerical) type
template <std::size_t Nelem, typename T, typename... Ts>
constexpr T partial_sum(T const t, Ts const... ts) {
  static_assert(Nelem < 1 + sizeof...(Ts), "Not enough elements to sum up");
  static_assert((std::is_same_v<T, Ts> && ...),
                "All arguments to be summed must be of the same type");
  if constexpr (Nelem == 0) {
    return 0;
  } else {
    return t + partial_sum<Nelem - 1>(ts...);
  }
}

// make a sequence of offsets based on the sizes of the given types
// the offset begins at 0 and the offset sequence is given in byte
// the sequence for the types <char, uint32_t,uint16_t> is e.g
// <0,1,5>
template <typename... Ts, size_t... Is>
constexpr auto
make_offset_sequence_impl(std::integer_sequence<std::size_t, Is...>) {
  return std::integer_sequence<size_t, (partial_sum<Is>(sizeof(Ts)...))...>();
}

template <typename... Ts> constexpr auto make_offset_sequence() {
  return make_offset_sequence_impl<Ts...>(std::index_sequence_for<Ts...>());
}

template <typename T, size_t OffsetBytes>
constexpr T elem_from_buffer_impl(std::uint8_t const *const buffer) {
  return *(reinterpret_cast<const T *>(buffer + OffsetBytes));
}

template <typename... Ts, size_t... Offsets>
constexpr std::tuple<Ts...> from_buffer_impl(uint8_t const *const buffer,
                                             std::index_sequence<Offsets...>) {
  std::tuple<Ts...> tup = {elem_from_buffer_impl<Ts, Offsets>(buffer)...};

  return tup;
}
} // namespace detail

template <typename... Ts, size_t N, typename BufType>
constexpr std::tuple<Ts...> copy_from_buffer(BufType const (&buffer)[N]) {
  static_assert(N > 0, "Cannot read from empty buffer");
  static_assert(sizeof...(Ts) > 0,
                "Must read at least one element from the buffer");
  static_assert((sizeof(Ts) + ...) <= N * sizeof(buffer[0]),
                "Not enough elements to read from in fixed size buffer");
  return detail::from_buffer_impl<Ts...>(
      reinterpret_cast<uint8_t const *>(&buffer[0]),
      detail::make_offset_sequence<Ts...>());
}

} // namespace mpsh
#endif // CPPBUFFER_STBUFFER_HPP
