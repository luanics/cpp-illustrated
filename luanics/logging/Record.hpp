#pragma once

#include "luanics/logging/Level.hpp"

#include <iosfwd>

namespace luanics {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Record
///
/// @brief A record of a single client logging request.
///
/// Contains meta-info about a logging message (level, file, line),
///  and has the ability to write the message to std::ostream.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Record {
public:
	virtual ~Record() {};

	virtual Level level() const = 0;
	virtual char const * file() const = 0;
	virtual unsigned line() const = 0;
	virtual void writeMessageTo(std::ostream & out) const = 0;

}; // class Record

}  // namespace logging
}  // namespace luanics
