#pragma once

#include "luanics/math/Operations.hpp"
#include "luanics/logging/Contract.hpp"

namespace luanics::math {

template <typename T>
T positiveModulo(T const a, T const b) {
	EXPECTS(b > T{0}, b);
	int result = a % b;
	if (result < 0) result += b;
	return result;
}

template <typename T>
int sign(T number) {
	return (T{0} < number) - (T{0} > number);
}

}  // namespace luanics::math
