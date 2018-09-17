#pragma once

#include <iostream>
#include <sstream>

namespace luanics::utility {

/// Sets "out" to a new value (empty by default)
void reset(std::ostringstream & out, std::string const & value = "");
/// Sets "in" to a new value (empty by default)
void reset(std::istringstream & in, std::string const & value = "");

} // namespace luanics::utility
