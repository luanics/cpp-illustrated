#pragma once

#include "luanics/meta/TypeTraits.hpp"

#include <string>
#include <vector>

namespace luanics::utility::strings {

std::vector<std::string> split(
	std::string const & splittee,
	std::string const & delimiters
);

template <typename T>
void join(
	std::vector<T> const & items,
	std::ostream & out,
	std::string const & delimiter
);

/// @pre delimiter != '/n'
char const * baseName(char const * const pathName, char const delimiter = '/');

template <typename T>
std::string toString(T const & t);

template <class T>
std::string toString(T * t);

template <class T>
T fromString(std::string const & s);

template <typename T>
std::string stringify(T const & t);

} // namespace luanics::utility::strings

#include "luanics/utility/Strings.ipp"
