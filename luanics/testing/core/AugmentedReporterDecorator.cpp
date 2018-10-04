#include "luanics/testing/core/AugmentedReporterDecorator.hpp"

namespace luanics::testing::core {

AugmentedReporterDecorator::AugmentedReporterDecorator(AugmentedReporter * decorated) :
	_decorated{decorated}
{}

bool AugmentedReporterDecorator::startReportOn(
	Component const & component,
	unsigned const depth
) {
	return _decorated->startReportOn(component, depth);
}

void AugmentedReporterDecorator::finishReportOn(
	Component const & component,
	unsigned const depth,
	Outcome const outcome
) {
	_decorated->finishReportOn(component, depth, outcome);
}

void AugmentedReporterDecorator::report(Error const & error) {
	_decorated->report(error);
}

void AugmentedReporterDecorator::report(Log const & log) {
	_decorated->report(log);
}

void AugmentedReporterDecorator::report(Result const & result) {
	_decorated->report(result);
}

} // namespace luanics::testing::core
