#include "luanics/testing/core/FirstFailDecorator.hpp"

namespace luanics::testing::core {

namespace {

bool isFail(Outcome const & outcome) {
	return outcome == Outcome::FAIL or outcome == Outcome::ERROR;
}

}

FirstFailDecorator::FirstFailDecorator(AugmentedReporter * decorated) :
	AugmentedReporterDecorator{decorated},
	_hasFailed{false}
{}

bool FirstFailDecorator::startReportOn(
	Component const & component,
	unsigned const depth
) {
	if (_hasFailed) {
		return false;
	}
	return AugmentedReporterDecorator::startReportOn(component, depth);
}

void FirstFailDecorator::finishReportOn(
	Component const & component,
	unsigned const depth,
	Outcome const outcome
) {
	_hasFailed = isFail(outcome);
	AugmentedReporterDecorator::finishReportOn(component, depth, outcome);
}

} // namespace luanics::testing::core
