#pragma once

#include "luanics/testing/core/AugmentedReporter.hpp"
#include "luanics/utility/Timer.hpp"

#include <chrono>
#include <iostream>
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
class StandardReporter : public core::AugmentedReporter {
public:
	enum Level {
		TEST_SUITE = 0,
		TEST_SET = 1,
		TEST = 2
	};

	StandardReporter(
		std::ostream * out,
		bool const isUsingColors = true,
		bool const isTerse = false
	);

	virtual bool startReportOn(
		core::Component const & component,
		unsigned const depth
	) override final;
	virtual void finishReportOn(
		core::Component const & component,
		unsigned const depth,
		core::Outcome const outcome
	) override final;

	virtual void report(core::Error const & error) override final;
	virtual void report(core::Log const & log) override final;
	virtual void report(core::Result const & result) override final;

	size_t numTestsPassed() const;
	size_t numTestsFailed() const;

private:
	bool startTestSuite();
	void finishTestSuite(core::Outcome const outcome);
	bool startTestSet(std::string const & name);
	void finishTestSet(std::string const & name, core::Outcome const outcome);
	bool startTest(std::string const & name);
	void finishTest(std::string const & name, core::Outcome const outcome);

	void writeFileLineIdentifier(char const * const filePath, int const line);

	std::ostream * _out;
	bool _isTerse;
	utility::Timer<std::chrono::high_resolution_clock> _testSuiteTimer;
	utility::Timer<std::chrono::high_resolution_clock> _testSetTimer;
	utility::Timer<std::chrono::high_resolution_clock> _testTimer;
	std::string _testSetName;
	size_t _globalTestCount;
	size_t _localTestCount;
	std::vector<std::string> _failedTests;
}; // class StandardReporter

} // namespace luanics::testing::unit
