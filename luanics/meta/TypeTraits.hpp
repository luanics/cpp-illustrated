#pragma once

#include "luanics/meta/Detection.hpp"
#include "luanics/meta/TypeTraits.ipp"

namespace luanics {

template<typename T>
constexpr bool IsStreamInsertable_v = IsDetected_v<details::StreamInsert_t, T>;

}  // namespace luanics

