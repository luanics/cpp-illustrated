#pragma once

#include "luanics/logging/Record.hpp"

#include <iosfwd>
#include <memory>
#include <tuple>

namespace luanics {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Record
///
/// @brief A logging Record that stores its message data in a tuple.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename ... ParamsT>
class TupleRecord : public Record {
public:
	TupleRecord(
		Level const level,
		char const * const file,
		unsigned const line,
		ParamsT && ... data
	);
	virtual Level level() const override final;
	virtual char const * file() const override final;
	virtual unsigned line() const override final;
	virtual void writeMessageTo(std::ostream & out) const override final;

private:
	Level const _level;
	char const * const _file;
	unsigned const _line;
	std::tuple<ParamsT ...> _messageData;
}; // class TupleRecord

template <typename ... ParamsT>
std::unique_ptr<Record> makeTupleRecord(
	Level const level,
	char const * const file,
	unsigned const line,
	ParamsT && ... data
);

}  // namespace logging
}  // namespace luanics

#include "luanics/logging/TupleRecord.ipp"
