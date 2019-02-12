#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"
#include "luanics/utility/Paths.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics::testing::unit {

namespace {

using namespace luanics::utility::streams;

std::string const BAR_BEGIN_DELIMITER = "[";
std::string const BAR_END_DELIMITER = "]";
std::string const INTRO_BAR   = "   TEST   ";
std::string const SUITE_BAR   = "==========";
std::string const CASE_BAR    = "----------";
std::string const LOG_BAR     = "    LOG   ";
std::string const RUN_BAR     = " RUN      ";
std::string const OK_BAR      = "       OK ";
std::string const PASS_BAR    = "  PASSED  ";
std::string const FAIL_BAR    = "  FAILED  ";
std::string const FAILURE_MESSAGE_INTRO = "FAILURE";
std::string const ERROR_MESSAGE_INTRO = "ERROR";
std::string const TESTCASE_TEST_DELIMITER = ".";
std::string const FAILED_TEST_BULLET = "* ";

std::ostream & introBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << boldBlue << INTRO_BAR << boldGreen << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & testSuiteBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << SUITE_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & testSetBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << CASE_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & logBar(std::ostream & out) {
	out << white << BAR_BEGIN_DELIMITER << LOG_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & runBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << RUN_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & okBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << OK_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & passBar(std::ostream & out) {
	out << boldGreen << BAR_BEGIN_DELIMITER << PASS_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & failBar(std::ostream & out) {
	out << boldRed << BAR_BEGIN_DELIMITER << FAIL_BAR << BAR_END_DELIMITER << plain;
	return out;
}

std::ostream & failedTestBullet(std::ostream & out) {
	out << boldRed << FAILED_TEST_BULLET << plain;
	return out;
}

/// Written to be used as an ostream manipulator
class context {

};

} // namespace

StandardReporter::StandardReporter(
	std::ostream * out,
	bool const isUsingColors,
	bool const isTerse
) :
	_out{out},
	_isTerse{isTerse},
	_testSuiteTimer{},
	_testSetTimer{},
	_testTimer{},
	_testSetName{},
	_globalTestCount{0},
	_localTestCount{0},
	_failedTests{}
{}

bool StandardReporter::startReportOn(core::Component const & component, unsigned const depth) {
	switch (depth) {
		case Level::TEST_SUITE: return startTestSuite();
		case Level::TEST_SET: return startTestSet(component.name());
		case Level::TEST: return startTest(component.name());
		default: LUANICS_UNREACHABLE(depth); return false;
	}
}

void StandardReporter::finishReportOn(core::Component const & component, unsigned const depth, core::Outcome const outcome) {
	switch (depth) {
		case Level::TEST_SUITE: finishTestSuite(outcome); break;
		case Level::TEST_SET: finishTestSet(component.name(), outcome); break;
		case Level::TEST: finishTest(component.name(), outcome); break;
		default: LUANICS_UNREACHABLE(depth);
	}
}

bool StandardReporter::startTestSuite() {
	*_out << testSuiteBar << std::endl;
	*_out << introBar << std::endl;
	*_out << std::endl;
	_testSuiteTimer.start();
	return true;
}

void StandardReporter::finishTestSuite(core::Outcome const outcome) {
	auto const suiteElapsed = _testSuiteTimer.elapsed();
	auto const msec = std::chrono::duration_cast<std::chrono::milliseconds>(suiteElapsed).count();
	*_out << testSuiteBar << " (" << msec << "msec)" << std::endl;
	*_out << passBar << " " << numTestsPassed() << " tests" << std::endl;
	if (numTestsFailed() > 0) {
		*_out << failBar << " " << numTestsFailed() << " tests" << std::endl;
		for (auto const & test: _failedTests) {
			*_out << failedTestBullet << test << std::endl;
		}
	}
	*_out << std::endl;
}

bool StandardReporter::startTestSet(std::string const & name) {
	_testSetName = name;
	_localTestCount = 0;
	if (_isTerse) {
		return true;
	}
	*_out << testSetBar << " " << _testSetName << std::endl;
	_testSetTimer.start();
	return true;
}

void StandardReporter::finishTestSet(std::string const & name, core::Outcome const outcome) {
	if (_isTerse) {
		return;
	}
	auto const caseElapsed = _testSetTimer.elapsed();
	auto const msec = std::chrono::duration_cast<std::chrono::milliseconds>(caseElapsed).count();
	*_out << testSetBar << " " << _localTestCount << " tests from " << _testSetName;
	*_out << " (" << msec << "msec)" << std::endl;
	*_out << std::endl;
}

bool StandardReporter::startTest(std::string const & name) {
	++_globalTestCount;
	++_localTestCount;
	if (_isTerse) {
		return true;
	}
	*_out << runBar << " " << _testSetName << TESTCASE_TEST_DELIMITER << name << std::endl;
	_testTimer.start();
	return true;
}

void StandardReporter::finishTest(std::string const & name, core::Outcome const outcome) {
	if (_isTerse) {
		return;
	}
	auto const testElapsed = _testTimer.elapsed();
	auto const msec = std::chrono::duration_cast<std::chrono::milliseconds>(testElapsed).count();
	switch (outcome) {
		case core::Outcome::NONE:
		case core::Outcome::PASS:
			*_out << okBar;
			break;
		case core::Outcome::FAIL:
		case core::Outcome::ERROR:
			*_out << failBar;
			_failedTests.push_back(_testSetName + TESTCASE_TEST_DELIMITER + name);
			break;
	}
	*_out << " " << _testSetName << TESTCASE_TEST_DELIMITER << name;
	*_out << " (" << msec << "msec)" << std::endl;
}

void StandardReporter::report(core::Error const & error) {
	*_out << ERROR_MESSAGE_INTRO;
	*_out << ": " << error.message << std::endl;
}

void StandardReporter::report(core::Log const & log) {
	*_out << logBar << "(";
	writeFileLineIdentifier(log.fileName, log.line);
	*_out << ") " << log.message << std::endl;
}

void StandardReporter::report(core::Result const & result) {
	if (result.isPass) {
		return;
	}
	*_out << FAILURE_MESSAGE_INTRO << " @ ";
	writeFileLineIdentifier(result.fileName, result.line);
	*_out << ": " << result.message << std::endl;
}

//*****************************************************************************
// Helpers
//*****************************************************************************

size_t StandardReporter::numTestsPassed() const {
	return _globalTestCount - numTestsFailed();
}

size_t StandardReporter::numTestsFailed() const {
	return _failedTests.size();
}

void StandardReporter::writeFileLineIdentifier(char const * const filePath, int const line) {
	*_out << utility::fileNameFrom(filePath) << ":" << line;
}

} // namespace luanics::testing::unit
