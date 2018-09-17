#pragma once

#include "luanics/logging/TupleRecord.hpp"
#include "luanics/utility/Tuples.hpp"

namespace luanics {
namespace logging {

template <typename ...ParamsT>
TupleRecord<ParamsT...>::TupleRecord(
	Level const level,
	char const * const file,
	unsigned const line,
	ParamsT && ... messageData
) :
	_level{level},
	_file{file},
	_line{line},
	_messageData(std::forward<ParamsT>(messageData)...)
{}

template <typename ...ParamsT>
Level TupleRecord<ParamsT...>::level() const {
	return _level;
}

template <typename ...ParamsT>
char const * TupleRecord<ParamsT...>::file() const {
	return _file;
}

template <typename ...ParamsT>
unsigned TupleRecord<ParamsT...>::line() const {
	return _line;
}

template <typename ...ParamsT>
void TupleRecord<ParamsT...>::writeMessageTo(std::ostream & out) const {
	luanics::tuples::write(_messageData, out);
}

template <typename ... ParamsT>
std::unique_ptr<Record> makeTupleRecord(
	Level const level,
	char const * const file,
	unsigned const line,
	ParamsT && ... data
) {
	return std::make_unique<TupleRecord<ParamsT...>>(level, file, line, std::forward<ParamsT>(data)...);
}

}  // namespace logging
}  // namespace luanics
