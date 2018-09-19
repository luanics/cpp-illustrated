#pragma once

#include <iosfwd>

namespace luanics {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Level
///
/// @brief Level of importance of a logging::Record.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
enum class Level {
	FATAL = 0,
	WARNING,
	INFO,
	DEBUG
};

std::ostream & operator<<(std::ostream & out, Level const level);

}  // namespace logging
}  // namespace luanics