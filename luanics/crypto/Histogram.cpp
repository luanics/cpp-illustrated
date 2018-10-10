#include "luanics/crypto/Histogram.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace luanics::crypto {

void histogram(std::map<int, int> const & frequencies, std::ostream & out) {
	if (frequencies.empty()) {
		return;
	}
	auto const minMaxResult = std::minmax_element(
		frequencies.begin(),
		frequencies.end(),
		[](auto const & lhs, auto const & rhs){return lhs.first < rhs.first;}
	);
	int const low = minMaxResult.first->first;
	int const high = minMaxResult.second->first;
	for (int i{low}; i <= high; ++i) {
		out
			<< std::left << std::setw(3) << std::setfill(' ') << i
			<< ":"
			<< std::setw(frequencies.at(i)) << std::setfill('*') << " " << std::endl;
	}
}

} // namespace luanics::crypto
