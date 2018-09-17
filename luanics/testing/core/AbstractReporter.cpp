#include "luanics/testing/core/AbstractReporter.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"

#include <cassert>

namespace luanics::testing::core {

/// @return false if wants to skip this node
bool AbstractReporter::startReportOn(Component const & component) {
	_outcomes.push(Outcome::NONE);
	auto const isStarted = doStartReportOn(component);
	if (not isStarted) {
		_outcomes.pop();
	}
	return isStarted;
}

void AbstractReporter::finishReportOn(Component const & component) {
	doFinishReportOn(component, _outcomes.top());

	// Update outcome for parent level
	auto const componentOutcome = _outcomes.top();
	_outcomes.pop();
	if (not _outcomes.empty()) {
		_outcomes.top() = combined(_outcomes.top(), componentOutcome);
	}
}

void AbstractReporter::report(Result const & result) {
	if (result.isPass) {
		_outcomes.top() = combined(_outcomes.top(), Outcome::PASS);
	}
	else {
		_outcomes.top() = combined(_outcomes.top(), Outcome::FAIL);
	}
	doReport(result);
}

void AbstractReporter::report(Error const & error) {
	_outcomes.top() = combined(_outcomes.top(), Outcome::ERROR);
	doReport(error);
}

void AbstractReporter::report(Log const & log) {
	doReport(log);
}

size_t AbstractReporter::depth() const {
	assert(not _outcomes.empty());
	return _outcomes.size() - 1;
}

} // namespace luanics::testing::core
