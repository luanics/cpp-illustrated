#include "luanics/utility/Strings.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <typeinfo>

namespace luanics::utility::strings {

namespace {
	const std::string TRUE_STRING("true");
	const std::string FALSE_STRING("false");
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

inline char const * baseName(char const * const pathName, char const delimiter) {
	assert(delimiter != '\n');
	auto found = strrchr(pathName, delimiter);
	return found == nullptr ? pathName : found + 1;
}

template <class T>
std::string toString(T * t) {
	std::ostringstream out;
	out << "0x" << std::setw(16) << std::setfill('0') << std::hex << std::noshowbase;
	out << reinterpret_cast<uint64_t>(t);
	return out.str();
}

template <>
inline std::string toString<char const>(char const * t) {
	return std::string(t);
}

template <class T>
std::string toString(T const & t) {
	std::ostringstream out;
	out << t;
	return out.str();
}

inline std::string toString(const bool value) {
	if (value == true) {
		return TRUE_STRING;
	}
	else {
		return FALSE_STRING;
	}
}

inline std::string toString(float const value) {
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << value;
	return out.str();
}

inline std::string toString(double const value) {
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << value;
	return out.str();
}

template <class T>
T fromString(std::string const & s) {
	std::istringstream in(s);
	T result;
	in >> result;
	return result;
}

template <typename T>
std::string stringify(T const & t) {
	return stringifyImpl(t);
}

template <typename T>
std::enable_if_t<IsStreamInsertable_v<T>, std::string> stringifyImpl(T const & t) {
	return toString(t);
}

template <typename T>
std::enable_if_t<not IsStreamInsertable_v<T>, std::string> stringifyImpl(T const & t) {
	return typeid(T).name();
}

} // namespace luanics::utility::strings
