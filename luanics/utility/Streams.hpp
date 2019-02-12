///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file utility::Streams
///
/// @brief An assortment of helper functions for iostreams.
///
/// * "reset" functions for stringstreams
/// * "color manip" functions for ostream
///   * Can toggle global behavior with setIsUsingAnsiCodes(bool).
///   * Set up as io manipulators, so can apply like this:
///     std::cout << green << "Happy St. Patrick's Day!" << plain << std::endl;
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <sstream>

namespace luanics::utility::streams {

/// Sets "out" to a new value (empty by default)
void reset(std::ostringstream & out, std::string const & value = "");
/// Sets "in" to a new value (empty by default)
void reset(std::istringstream & in, std::string const & value = "");

bool isUsingAnsiCodes();
void setIsUsingAnsiCodes(bool value);

std::ostream & plain(std::ostream & out);

std::ostream & black(std::ostream & out);
std::ostream & lightGray(std::ostream & out);
std::ostream & darkGray(std::ostream & out);
std::ostream & white(std::ostream & out);

std::ostream & red(std::ostream & out);
std::ostream & green(std::ostream & out);
std::ostream & brown(std::ostream & out);
std::ostream & blue(std::ostream & out);
std::ostream & magenta(std::ostream & out);
std::ostream & cyan(std::ostream & out);

std::ostream & boldRed(std::ostream & out);
std::ostream & boldGreen(std::ostream & out);
std::ostream & boldYellow(std::ostream & out);
std::ostream & boldBlue(std::ostream & out);
std::ostream & boldMagenta(std::ostream & out);
std::ostream & boldCyan(std::ostream & out);

} // namespace luanics::utility::streams
