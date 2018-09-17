#pragma once

#include <iterator>

namespace luanics {

template <typename T>
struct ReverseWrapper {T & wrapped;};

template <typename T>
auto begin(ReverseWrapper<T> wrapper) {return std::rbegin(wrapper.wrapped);}

template <typename T>
auto end(ReverseWrapper<T> wrapper) {return std::rend(wrapper.wrapped);}

template <typename T>
ReverseWrapper<T> reverse(T && t) {return {t};}

} // namespace luanics
