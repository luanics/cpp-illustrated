#pragma once

#include "luanics/testing/core/Outcome.hpp"

namespace luanics::testing::core {

class Component;
class Error;
class Log;
class Result;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class AugmentedReporter
///
/// @brief Adds "depth" and "outcome" to the Reporter callbacks.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class AugmentedReporter {
public:
	virtual ~AugmentedReporter() = default;

	/// @return false if wants to skip this component
	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) = 0;
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) = 0;

	virtual void report(Error const & error) = 0;
	virtual void report(Log const & log) = 0;
	virtual void report(Result const & result) = 0;

}; // class AugmentedReporter

} // namespace luanics::testing::core
