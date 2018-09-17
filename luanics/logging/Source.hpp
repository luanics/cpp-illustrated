#pragma once

#include <memory>

namespace luanics {
namespace logging {

class Filter;
class Record;
class Sink;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Source
///
/// @brief Front-end of logging framework.
///
/// Accepts logging::Record submitted from user, and hands it off to Sink.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Source {
public:
	virtual void submit(std::unique_ptr<Record> record) = 0;

	virtual void setFilter(std::unique_ptr<Filter> filter) = 0;
	virtual void setSink(std::unique_ptr<Sink> sink) = 0;

	virtual ~Source() {}
}; // class Source

}  // namespace logging
}  // namespace luanics
