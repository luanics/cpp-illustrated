#pragma once

#include <type_traits>

namespace luanics {
namespace meta {

template <bool... Vs>
bool constexpr requires = std::conjunction<std::bool_constant<Vs>...>::value;

} // namespace meta
} // namespace luanics
