#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file math/FloatingPoint.hpp
///
/// @brief Additional functions for floating-point types.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace luanics::math {

/// @returns |x - y| / min(|x|, |y|)
template <typename T>
T relativeDifference(T x, T y);

/// Checks if the relative difference of x and y is within tolerance.
/// Default tolerance is 1 part in a million.
template <typename T>
bool areClose(T x, T y, T tolerance = 1e-6);

template <typename ContainerT>
bool areAllClose(
	ContainerT const & xs,
	ContainerT const & ys,
	typename ContainerT::value_type tolerance = 1e-6
);

}  // namespace luanics::math

#include "luanics/math/FloatingPoint.ipp"
