#pragma once

#include "luanics/logging/Filter.hpp"
#include "luanics/logging/Record.hpp"
#include "luanics/logging/Sink.hpp"
#include "luanics/logging/Source.hpp"

#include <iostream>
#include <memory>

namespace luanics::logging {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class SimpleSource
///
/// @brief Logging Source suitable for single-threaded applications.
///
/// All Records submitted are immediately handed off to Sink in same thread.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SimpleSource : public Source {
public:
	SimpleSource(); ///< Installs NoFilter and SimpleSink

	virtual void submit(std::unique_ptr<Record> record) override final;
	virtual void setFilter(std::unique_ptr<Filter> filter) override final;
	virtual void setSink(std::unique_ptr<Sink> sink) override final;

private:
	std::unique_ptr<Filter> _filter;
	std::unique_ptr<Sink> _sink;
}; // class SimpleSource

}  // namespace luanics::logging
