#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"
#include "luanics/utility/Ansi.hpp"
#include "luanics/utility/Paths.hpp"

namespace luanics::testing::unit {

namespace {

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

}

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
	_introBar{},
	_testSuiteBar{},
	_testSetBar{},
	_logBar{},
	_runBar{},
	_okBar{},
	_passBar{},
	_failBar{},
	_failedTestBullet{},
	_failedTests{}
{
	if (isUsingColors) {
		setupUsingAnsiColors();
	}
	else {
		setupUsingNoColors();
	}
}

bool StandardReporter::startTestSuite() {
	*_out << _testSuiteBar << std::endl;
	*_out << _introBar << std::endl;
	*_out << std::endl;
	_testSuiteTimer.start();
	return true;
}

void StandardReporter::finishTestSuite(core::Outcome const outcome) {
	auto const suiteElapsed = _testSuiteTimer.elapsed();
	auto const msec = std::chrono::duration_cast<std::chrono::milliseconds>(suiteElapsed).count();
	*_out << _testSuiteBar << " (" << msec << "msec)" << std::endl;
	*_out << _passBar << " " << numTestsPassed() << " tests" << std::endl;
	if (numTestsFailed() > 0) {
		*_out << _failBar << " " << numTestsFailed() << " tests" << std::endl;
		for (auto const & test: _failedTests) {
			*_out << _failedTestBullet << test << std::endl;
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
	*_out << _testSetBar << " " << _testSetName << std::endl;
	_testSetTimer.start();
	return true;
}

void StandardReporter::finishTestSet(std::string const & name, core::Outcome const outcome) {
	if (_isTerse) {
		return;
	}
	auto const caseElapsed = _testSetTimer.elapsed();
	auto const msec = std::chrono::duration_cast<std::chrono::milliseconds>(caseElapsed).count();
	*_out << _testSetBar << " " << _localTestCount << " tests from " << _testSetName;
	*_out << " (" << msec << "msec)" << std::endl;
	*_out << std::endl;
}

bool StandardReporter::startTest(std::string const & name) {
	++_globalTestCount;
	++_localTestCount;
	if (_isTerse) {
		return true;
	}
	*_out << _runBar << " " << _testSetName << TESTCASE_TEST_DELIMITER << name << std::endl;
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
			*_out << _okBar;
			break;
		case core::Outcome::FAIL:
		case core::Outcome::ERROR:
			*_out << _failBar;
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
	*_out << _logBar << "(";
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

void StandardReporter::setupUsingAnsiColors() {
	using namespace utility::ansi;
	_introBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + BOLD_BLUE + INTRO_BAR + BOLD_GREEN + BAR_END_DELIMITER + RESET;
	_testSuiteBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + SUITE_BAR + BAR_END_DELIMITER + RESET;
	_testSetBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + CASE_BAR + BAR_END_DELIMITER + RESET;
	_logBar = WHITE + BAR_BEGIN_DELIMITER + LOG_BAR + BAR_END_DELIMITER + RESET;
	_runBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + RUN_BAR + BAR_END_DELIMITER + RESET;
	_okBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + OK_BAR + BAR_END_DELIMITER + RESET;
	_passBar = BOLD_GREEN + BAR_BEGIN_DELIMITER + PASS_BAR + BAR_END_DELIMITER + RESET;
	_failBar = BOLD_RED + BAR_BEGIN_DELIMITER + FAIL_BAR + BAR_END_DELIMITER + RESET;
	_failedTestBullet = BOLD_RED + FAILED_TEST_BULLET + RESET;
}

void StandardReporter::setupUsingNoColors() {
	_introBar = BAR_BEGIN_DELIMITER + INTRO_BAR + BAR_END_DELIMITER;
	_testSuiteBar = BAR_BEGIN_DELIMITER + SUITE_BAR + BAR_END_DELIMITER;
	_testSetBar = BAR_BEGIN_DELIMITER + CASE_BAR + BAR_END_DELIMITER;
	_logBar = BAR_BEGIN_DELIMITER + LOG_BAR + BAR_END_DELIMITER;
	_runBar = BAR_BEGIN_DELIMITER + RUN_BAR + BAR_END_DELIMITER;
	_okBar = BAR_BEGIN_DELIMITER + OK_BAR + BAR_END_DELIMITER;
	_passBar = BAR_BEGIN_DELIMITER + PASS_BAR + BAR_END_DELIMITER;
	_failBar = BAR_BEGIN_DELIMITER + FAIL_BAR + BAR_END_DELIMITER;
	_failedTestBullet = FAILED_TEST_BULLET;
}

void StandardReporter::writeFileLineIdentifier(char const * const filePath, int const line) {
	*_out << utility::fileNameFrom(filePath) << ":" << line;
}

} // namespace luanics::testing::unit
