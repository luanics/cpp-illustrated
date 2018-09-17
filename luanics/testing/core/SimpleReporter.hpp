#pragma once

#include "luanics/testing/core/Reporter.hpp"

#include <cstddef>

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class SimpleReporter
///
/// @brief Reporter that simply counts the kinds of outcomes.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class SimpleReporter : public Reporter {
public:
	SimpleReporter();

	virtual bool startReportOn(Component const & component) override final;
	virtual void finishReportOn(Component const & component) override final;

	virtual void report(Result const & result) override final;
	virtual void report(Error const & error) override final;
	virtual void report(Log const & log) override final;

	std::size_t numPassResults() const;
	std::size_t numFailResults() const;
	std::size_t numErrors() const;
	std::size_t numLogs() const;

private:
	std::size_t _numPassResults;
	std::size_t _numFailResults;
	std::size_t _numErrors;
	std::size_t _numLogs;
}; // class SimpleReporter

} // namespace luanics::testing::core
