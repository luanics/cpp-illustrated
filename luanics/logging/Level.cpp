#include "luanics/logging/Level.hpp"

#include <iostream>

namespace {

constexpr auto FATAL_STRING = "FATAL";
constexpr auto WARNING_STRING = "WARNING";
constexpr auto INFO_STRING = "INFO";
constexpr auto DEBUG_STRING = "DEBUG";

}

namespace luanics {
namespace logging {

std::ostream & operator<<(std::ostream & out, Level const level) {
	switch (level) {
		case Level::FATAL: out << FATAL_STRING; break;
		case Level::WARNING: out << WARNING_STRING; break;
		case Level::INFO: out << INFO_STRING; break;
		case Level::DEBUG: out << DEBUG_STRING; break;
	}
	return out;
}

}  // namespace logging
}  // namespace luanics
