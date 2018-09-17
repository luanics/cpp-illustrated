#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file Manipulation.hpp
///
/// @brief Helper functions for manipulating std::strings.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace luanics::string {

/// Writes items to out using operator<<, separated by delimiter
/// @param[in] items is list of items to join
/// @param[out] out is ostream to which items are written
/// @param[in] delimiter is used to separate items
template <typename T>
void join(
	std::vector<T> const & items,
	std::ostream & out,
	std::string const & delimiter
);

/// @returns a vector holding the elements of splittee string split at delimiters
/// @param[in] splittee is the string to split
/// @param[in] delimiters is a string containing all delimiters
std::vector<std::string> split(
	std::string const & splittee,
	std::string const & delimiters
);

} // namespace luanics::string

#include "luanics/string/Manipulation.ipp"
