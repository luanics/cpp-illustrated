#pragma once

#include "luanics/benchmarking/Reporter.hpp"

#include <iostream>

namespace luanics::benchmarking {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class TableReporter
///
/// @brief TableDisplays benchmarking::Results in a table format
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class TableReporter final : public Reporter {
public:
	TableReporter(std::ostream * out);

	virtual void report(Result const & result) final;

private:
	std::ostream & out();
	void printHeader();

	std::ostream * _out;
}; // class TableReporter

} // namespace luanics::benchmarking
