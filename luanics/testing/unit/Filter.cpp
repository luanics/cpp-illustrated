#include "luanics/string/Matcher.hpp"
#include "luanics/testing/unit/Filter.hpp"

namespace luanics::testing::unit {

Filter::Filter(
	std::unique_ptr<luanics::string::Matcher> testSetMatcher,
	std::unique_ptr<luanics::string::Matcher> testMatcher,
	Reporter * filtered
) :
	_testSetMatcher{std::move(testSetMatcher)},
	_testMatcher{std::move(testMatcher)},
	_filtered{filtered}
{}

bool Filter::startTestSuite() {
	return _filtered->startTestSuite();
}

void Filter::finishTestSuite(core::Outcome const outcome) {
	_filtered->finishTestSuite(outcome);
}

bool Filter::startTestSet(std::string const & name) {
	if (_testSetMatcher->operator()(name)) {
		return _filtered->startTestSet(name);
	}
	else {
		return false;
	}
}

void Filter::finishTestSet(std::string const & name, core::Outcome const outcome) {
	_filtered->finishTestSet(name, outcome);
}

bool Filter::startTest(std::string const & name) {
	if (_testMatcher->operator()(name)) {
		return _filtered->startTest(name);
	}
	else {
		return false;
	}
}

void Filter::finishTest(std::string const & name, core::Outcome const outcome) {
	_filtered->finishTest(name, outcome);
}

void Filter::report(core::Error const & error) {
	_filtered->report(error);
}

void Filter::report(core::Log const & log) {
	_filtered->report(log);
}

void Filter::report(core::Result const & result) {
	_filtered->report(result);
}

} // namespace luanics::testing::unit
