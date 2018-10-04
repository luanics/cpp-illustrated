#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/AugmentedReporter.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/ReporterAugmenter.hpp"
#include "luanics/testing/core/Result.hpp"

namespace luanics::testing::core {

ReporterAugmenter::ReporterAugmenter(AugmentedReporter * adapted) :
	_adapted{adapted},
	_outcomes{}
{}

bool ReporterAugmenter::startReportOn(Component const & component) {
	_outcomes.push(Outcome::NONE);
	bool const isStarted = _adapted->startReportOn(component, depth());
	if (not isStarted) {
		_outcomes.pop();
	}
	return isStarted;
}

void ReporterAugmenter::finishReportOn(Component const & component) {
	_adapted->finishReportOn(component, depth(), _outcomes.top());

	// Update outcome for parent level
	Outcome const componentOutcome = _outcomes.top();
	_outcomes.pop();
	if (not _outcomes.empty()) {
		_outcomes.top() = combined(_outcomes.top(), componentOutcome);
	}
}

void ReporterAugmenter::report(Error const & error) {
	_outcomes.top() = combined(_outcomes.top(), Outcome::ERROR);
	_adapted->report(error);
}

void ReporterAugmenter::report(Log const & log) {
	_adapted->report(log);
}

void ReporterAugmenter::report(Result const & result) {
	if (result.isPass) {
		_outcomes.top() = combined(_outcomes.top(), Outcome::PASS);
	}
	else {
		_outcomes.top() = combined(_outcomes.top(), Outcome::FAIL);
	}
	_adapted->report(result);
}

unsigned ReporterAugmenter::depth() const {
	LUANICS_ASSERT(not _outcomes.empty());
	return _outcomes.size() - 1;
}

} // namespace luanics::testing::core
