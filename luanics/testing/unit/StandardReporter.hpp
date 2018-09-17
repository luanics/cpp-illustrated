#pragma once

#include "luanics/testing/unit/Reporter.hpp"
#include "luanics/utility/Timer.hpp"

#include <chrono>
#include <vector>

namespace luanics::testing::unit {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class StandardReporter
///
/// @brief A unit-test Reporter with "gtest"-style output.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class StandardReporter : public Reporter {
public:
	StandardReporter(
		std::ostream * out,
		bool const isUsingColors = true,
		bool const isTerse = false
	);

	virtual bool startTestSuite() override final;
	virtual void finishTestSuite(core::Outcome const outcome) override final;

	virtual bool startTestSet(std::string const & name) override final;
	virtual void finishTestSet(std::string const & name, core::Outcome const outcome) override final;

	virtual bool startTest(std::string const & name) override final;
	virtual void finishTest(std::string const & name, core::Outcome const outcome) override final;

	virtual void report(core::Error const & error) override final;
	virtual void report(core::Log const & log) override final;
	virtual void report(core::Result const & result) override final;

private:
	void setupUsingAnsiColors();
	void setupUsingNoColors();

	size_t numTestsPassed() const;
	size_t numTestsFailed() const;

	void writeFileLineIdentifier(char const * const filePath, int const line);

	std::ostream * _out;
	bool _isTerse;
	utility::Timer<std::chrono::high_resolution_clock> _testSuiteTimer;
	utility::Timer<std::chrono::high_resolution_clock> _testSetTimer;
	utility::Timer<std::chrono::high_resolution_clock> _testTimer;
	std::string _testSetName;
	size_t _globalTestCount;
	size_t _localTestCount;
	std::string _introBar;
	std::string _testSuiteBar;
	std::string _testSetBar;
	std::string _logBar;
	std::string _runBar;
	std::string _okBar;
	std::string _passBar;
	std::string _failBar;
	std::string _failedTestBullet;
	std::vector<std::string> _failedTests;
}; // class StandardReporter

} // namespace luanics::testing::unit
