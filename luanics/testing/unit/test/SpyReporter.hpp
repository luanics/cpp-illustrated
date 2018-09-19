#pragma once

#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/unit/Reporter.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace luanics::testing::unit {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class SpyReporter
///
/// @brief Simple Reporter test double that keeps track of calls for testing.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class SpyReporter : public Reporter {
public:

	unsigned numStartTestSuiteCalls() const {return _numStartTestSuiteCalls;}
	std::vector<core::Outcome> const & finishTestSuiteCalls() const {return _finishTestSuiteCalls;}
	std::vector<std::string> const & startTestSetCalls() const {return _startTestSetCalls;}
	std::vector<std::pair<std::string, core::Outcome>> const & finishTestSetCalls() const {return _finishTestSetCalls;}
	std::vector<std::string> const & startTestCalls() const {return _startTestCalls;}
	std::vector<std::pair<std::string, core::Outcome>> const & finishTestCalls() const {return _finishTestCalls;}
	std::vector<core::Error> const & reportErrorCalls() const {return _reportErrorCalls;}
	std::vector<core::Log> const & reportLogCalls() const {return _reportLogCalls;}
	std::vector<core::Result> const & reportResultCalls() const {return _reportResultCalls;}

	virtual bool startTestSuite() override final {
		++_numStartTestSuiteCalls;
		return true;
	}
	virtual void finishTestSuite(core::Outcome const outcome) override final {
		_finishTestSuiteCalls.push_back(outcome);
	}
	virtual bool startTestSet(std::string const & name) override final {
		_startTestSetCalls.push_back(name);
		return true;
	}
	virtual void finishTestSet(std::string const & name, core::Outcome const outcome) override final {
		_finishTestSetCalls.push_back({name, outcome});
	}
	virtual bool startTest(std::string const & name) override final {
		_startTestCalls.push_back(name);
		return true;
	}
	virtual void finishTest(std::string const & name, core::Outcome const outcome) override final{
		_finishTestCalls.push_back({name, outcome});
	}
	virtual void report(core::Error const & error) override final {
		_reportErrorCalls.push_back(error);
	}
	virtual void report(core::Log const & log) override final {
		_reportLogCalls.push_back(log);
	}
	virtual void report(core::Result const & result) override final {
		_reportResultCalls.push_back(result);
	}

private:
	unsigned _numStartTestSuiteCalls;
	std::vector<core::Outcome> _finishTestSuiteCalls;
	std::vector<std::string> _startTestSetCalls;
	std::vector<std::pair<std::string, core::Outcome>> _finishTestSetCalls;
	std::vector<std::string> _startTestCalls;
	std::vector<std::pair<std::string, core::Outcome>> _finishTestCalls;
	std::vector<core::Error> _reportErrorCalls;
	std::vector<core::Log> _reportLogCalls;
	std::vector<core::Result> _reportResultCalls;

}; // class SpyReporter

} // namespace luanics::testing::unit
