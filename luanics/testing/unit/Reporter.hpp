#pragma once

#include "luanics/testing/core/Outcome.hpp"

#include <string>

namespace luanics::testing {

namespace core {
	class Error;
	class Log;
	class Result;
}

namespace unit {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Reporter
///
/// @brief Reporter tailored to the structure of unit tests.
///
/// Follows approach similar to Builder design pattern.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Reporter {
public:
	virtual ~Reporter() = default;

	virtual bool startTestSuite() = 0;
	/// Not called if startTestSuite() returns false
	virtual void finishTestSuite(core::Outcome const outcome) = 0;

	virtual bool startTestSet(std::string const & name) = 0;
	/// Not called if startTestCase() returns false
	virtual void finishTestSet(std::string const & name, core::Outcome const outcome) = 0;

	virtual bool startTest(std::string const & name) = 0;
	/// Not called if startTest() returns false
	virtual void finishTest(std::string const & name, core::Outcome const outcome) = 0;

	virtual void report(core::Error const & error) = 0;
	virtual void report(core::Log const & log) = 0;
	virtual void report(core::Result const & result) = 0;

}; // class Reporter

} // namespace unit
} // namespace luanics::testing
