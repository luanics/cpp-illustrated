#include "luanics/string/Conversion.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace luanics::string {

namespace {
	const std::string TRUE_STRING("true");
	const std::string FALSE_STRING("false");
}

std::vector<std::string> split(
	std::string const & splittee,
	std::string const & delimiters
) {
	std::vector<std::string> result;
	if (splittee.empty()) {
		return result;
	}
	auto first = splittee.find_first_not_of(delimiters);
	auto second = splittee.find_first_of(delimiters);
	while (second != std::string::npos) {
		auto size = second - first;
		result.push_back(splittee.substr(first, size));
		first = splittee.find_first_not_of(delimiters, second);
		second = splittee.find_first_of(delimiters, first);
	}
	if (first != std::string::npos) {
		result.push_back(splittee.substr(first));
	}
	return result;
}
std::string toString(const bool value) {
	if (value == true) {
		return TRUE_STRING;
	}
	else {
		return FALSE_STRING;
	}
}

} // namespace luanics::string
