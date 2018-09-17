#pragma once

namespace luanics::testing::core {

class Component;
class Error;
class Log;
class Result;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class Reporter
///
/// @brief Gathers the results of running the test hierarchy.
///
/// Uses Visitor pattern.
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class Reporter {
public:
	virtual ~Reporter() = default;

	/// @return false if wants to skip this component
	virtual bool startReportOn(Component const & component) = 0;
	/// NOT called if startReportOn() returns false.
	virtual void finishReportOn(Component const & component) = 0;

	virtual void report(Error const & error) = 0;
	virtual void report(Log const & log) = 0;
	virtual void report(Result const & result) = 0;
};

} // namespace luanics::testing::core
