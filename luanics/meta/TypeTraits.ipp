#pragma once

#include <iostream>
#include <type_traits>

namespace luanics {
namespace details {

template<typename T>
using StreamInsert_t = decltype(std::declval<std::ostream &>() << std::declval<T>());

}
}