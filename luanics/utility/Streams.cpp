#include "luanics/utility/Streams.hpp"

namespace {

bool isUsingAnsiCodes_ = true;

static constexpr char const * PLAIN = "\033[0m";
static constexpr char const * BLACK = "\033[30m";
static constexpr char const * RED = "\033[31m";
static constexpr char const * GREEN = "\033[32m";
static constexpr char const * BROWN = "\033[33m";
static constexpr char const * BLUE = "\033[34m";
static constexpr char const * MAGENTA = "\033[35m";
static constexpr char const * CYAN = "\033[36m";
static constexpr char const * LIGHT_GRAY = "\033[37m";
static constexpr char const * DARK_GRAY  = "\033[1m\033[30m";
static constexpr char const * BOLD_RED = "\033[1m\033[31m";
static constexpr char const * BOLD_GREEN = "\033[1m\033[32m";
static constexpr char const * BOLD_YELLOW = "\033[1m\033[33m";
static constexpr char const * BOLD_BLUE = "\033[1m\033[34m";
static constexpr char const * BOLD_MAGENTA = "\033[1m\033[35m";
static constexpr char const * BOLD_CYAN = "\033[1m\033[36m";
static constexpr char const * WHITE = "\033[1m\033[37m";

}

namespace luanics::utility::streams {

void reset(std::ostringstream & out, std::string const & value) {
	out.str(value);
	out.clear();
}

void reset(std::istringstream & in, std::string const & value) {
	in.str(value);
	in.clear();
}

bool isUsingAnsiCodes() {
	return isUsingAnsiCodes_;
}

void setIsUsingAnsiCodes(bool value) {
	isUsingAnsiCodes_ = value;
}

std::ostream & plain(std::ostream & out) {
	if (isUsingAnsiCodes()) out << PLAIN;
	return out;
}

std::ostream & black(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BLACK;
	return out;
}

std::ostream & lightGray(std::ostream & out) {
	if (isUsingAnsiCodes()) out << LIGHT_GRAY;
	return out;
}

std::ostream & darkGray(std::ostream & out) {
	if (isUsingAnsiCodes()) out << DARK_GRAY;
	return out;
}

std::ostream & white(std::ostream & out) {
	if (isUsingAnsiCodes()) out << WHITE;
	return out;
}

std::ostream & red(std::ostream & out) {
	if (isUsingAnsiCodes()) out << RED;
	return out;
}

std::ostream & green(std::ostream & out) {
	if (isUsingAnsiCodes()) out << GREEN;
	return out;
}

std::ostream & brown(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BROWN;
	return out;
}

std::ostream & blue(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BLUE;
	return out;
}

std::ostream & magenta(std::ostream & out) {
	if (isUsingAnsiCodes()) out << MAGENTA;
	return out;
}

std::ostream & cyan(std::ostream & out) {
	if (isUsingAnsiCodes()) out << CYAN;
	return out;
}

std::ostream & boldRed(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_RED;
	return out;
}

std::ostream & boldGreen(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_GREEN;
	return out;
}

std::ostream & boldYellow(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_YELLOW;
	return out;
}

std::ostream & boldBlue(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_BLUE;
	return out;
}

std::ostream & boldMagenta(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_MAGENTA;
	return out;
}

std::ostream & boldCyan(std::ostream & out) {
	if (isUsingAnsiCodes()) out << BOLD_CYAN;
	return out;
}

} // namespace luanics::utility::streams
