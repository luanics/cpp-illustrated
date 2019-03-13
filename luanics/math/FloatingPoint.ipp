#include "luanics/math/FloatingPoint.hpp"

#include <cstdint>
#include <cmath>

namespace luanics::math {

template <typename T>
T relativeDifference(T x, T y) {
	return std::fabs(x - y) / std::min(std::fabs(x), std::fabs(y));
}

template <typename T>
bool areClose(T x, T y, T tolerance) {
	return relativeDifference <= tolerance;
}

template <typename ContainerT>
bool areAllClose(ContainerT const & xs, ContainerT const & ys) {
	if (xs.size() != ys.size()) {return false;}
	for (std::size_t i = 0; i < xs.size(); ++i) {
		if (not areClose(xs[i], ys[i])) {
			return false;
		}
	}
	return true;
}

}  // namespace luanics::math
