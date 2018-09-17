#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file Conversion.hpp
///
/// @brief Helper functions for converting to and from std::strings.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/meta/TypeTraits.hpp"

#include <iomanip>
#include <sstream>
#include <string>

namespace luanics::string {

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

std::string toString(const bool value);

inline std::string toString(double const value) {
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << value;
	return out.str();
}

inline std::string toString(float const value) {
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
std::enable_if_t<IsStreamInsertable_v<T>, std::string> stringify(T const & t) {
	return toString(t);
}

template <typename T>
std::enable_if_t<not IsStreamInsertable_v<T>, std::string> stringify(T const & t) {
	return typeid(T).name();
}

} // namespace luanics::string
