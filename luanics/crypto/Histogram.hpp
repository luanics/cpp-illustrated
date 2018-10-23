#pragma once

#include <map>
#include <iosfwd>

namespace luanics::crypto {

void histogram(
	std::map<int, int> const & frequencies,
	std::ostream & out,
	int const inverseScale = 1
);

} // namespace luanics::crypto
