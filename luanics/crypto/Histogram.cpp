#include "luanics/crypto/Histogram.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace luanics::crypto {

void histogram(std::map<int, int> const & frequencies, std::ostream & out, int const inverseScale) {
	if (frequencies.empty()) {
		return;
	}
	auto const minMaxResult = std::minmax_element(
		frequencies.begin(),
		frequencies.end(),
		[](auto const & lhs, auto const & rhs){return lhs.first < rhs.first;}
	);
	int const low = minMaxResult.first->first - 1;
	int const high = minMaxResult.second->first + 1;
	for (int i{low}; i <= high; ++i) {
		out << std::left << std::setw(3) << std::setfill(' ') << i << "|";
		auto const position = frequencies.find(i);
		bool const isFound = position != frequencies.end();
		if (isFound) {
			out << std::string(position->second/inverseScale, '*');
		}
		out << std::endl;
	}
}

} // namespace luanics::crypto
