#include "luanics/testing/core/FirstFailFilter.hpp"

namespace luanics::testing::core {

namespace {

bool isFail(Outcome const & outcome) {
	return outcome == Outcome::FAIL or outcome == Outcome::ERROR;
}

}

FirstFailFilter::FirstFailFilter(AugmentedReporter * filtered) :
	AugmentedReporterDecorator{filtered},
	_hasFailed{false}
{}

bool FirstFailFilter::startReportOn(
	Component const & component,
	unsigned const depth
) {
	if (_hasFailed) {
		return false;
	}
	return AugmentedReporterDecorator::startReportOn(component, depth);
}

void FirstFailFilter::finishReportOn(
	Component const & component,
	unsigned const depth,
	Outcome const outcome
) {
	_hasFailed = isFail(outcome);
	AugmentedReporterDecorator::finishReportOn(component, depth, outcome);
}

} // namespace luanics::testing::core
