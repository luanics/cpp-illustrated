#include "luanics/string/Manipulation.hpp"

namespace luanics::string {

template <typename T>
void join(
	std::vector<T> const & items,
	std::ostream & out,
	std::string const & delimiter
) {
	if (items.empty()) return;
	for (std::size_t i = 0; i < items.size()-1; ++i) {
		out << items[i] << delimiter;
	}
	out << items.back();
}

inline std::vector<std::string> split(
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

} // namespace luanics::string
