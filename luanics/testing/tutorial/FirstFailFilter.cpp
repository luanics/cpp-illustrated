#include "luanics/testing/tutorial/FirstFailFilter.hpp"

namespace luanics::testing::tutorial {

namespace {

bool isFail(core::Outcome const outcome) {
	return outcome == core::Outcome::FAIL or outcome == core::Outcome::ERROR;
}

}

FirstFailFilter::FirstFailFilter(luanics::testing::tutorial::Reporter * filtered) :
	_filtered{filtered},
	_hasFailed{false}
{}

bool FirstFailFilter:: startTutorial() {
	return _filtered->startTutorial();
}

void FirstFailFilter::finishTutorial(core::Outcome const outcome) {
	_hasFailed = isFail(outcome);
	_filtered->finishTutorial(outcome);
}

bool FirstFailFilter:: startPart(std::string const & name) {
	if (_hasFailed) {
		return false;
	}
	return _filtered->startPart(name);
}

void FirstFailFilter::finishPart(std::string const & name, core::Outcome const outcome) {
	_hasFailed = isFail(outcome);
	_filtered->finishPart(name, outcome);
}

bool FirstFailFilter:: startChapter(std::string const & name) {
	if (_hasFailed) {
		return false;
	}
	return _filtered->startChapter(name);
}

void FirstFailFilter::finishChapter(std::string const & name, core::Outcome const outcome) {
	_hasFailed = isFail(outcome);
	return _filtered->finishChapter(name, outcome);
}

bool FirstFailFilter:: startSection(std::string const & name) {
	if (_hasFailed) {
		return false;
	}
	return _filtered->startSection(name);
}

void FirstFailFilter::finishSection(std::string const & name, core::Outcome const outcome) {
	_hasFailed = isFail(outcome);
	_filtered->finishSection(name, outcome);
}

void FirstFailFilter::report(core::Error const & error) {
	_filtered->report(error);
}

void FirstFailFilter::report(core::Log const & log) {
	_filtered->report(log);
}

void FirstFailFilter::report(core::Result const & result) {
	_filtered->report(result);
}

} // namespace luanics::testing::tutorial
