#pragma once

#include "luanics/math/Operations.hpp"

namespace luanics {
namespace math {

// See http://stackoverflow.com/questions/4003232/how-to-code-a-modulo-operator-in-c-c-obj-c-that-handles-negative-numbers?rq=1
template <typename T>
T modulo(T const a, T const b) {
   if (b < 0) return modulo(-a, -b);
   int result = a % b;
   if(result < 0) result += b;
   return result;
}

template <typename T>
int sign(T number) {
	return (T{0} < number) - (T{0} > number);
}

}  // namespace math
}  // namespace luanics
