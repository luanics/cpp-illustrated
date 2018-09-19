#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file math/Operations.hpp
///
/// @brief Basic mathematical operations not provided by Standard Library.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace luanics {
namespace math {

/// @returns the remainder of dividend / divisor
/// Modulo implemented using "Euclidean definition", so result always positive
template <typename T>
T modulo(T const dividend, T const divisor);

/// @returns -1 if negative, 0 if zero, 1 if positive
template <typename T>
int sign(T number);

}  // namespace math
}  // namespace luanics

#include "luanics/math/Operations.ipp"
