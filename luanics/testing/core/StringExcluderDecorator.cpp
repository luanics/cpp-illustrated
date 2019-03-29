#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/core/StringExcluderDecorator.hpp"

namespace luanics::testing::core {

StringExcluderDecorator::StringExcluderDecorator(
	AugmentedReporter * decorated,
	std::string target
) :
	AugmentedReporterDecorator{decorated},
	_target{std::move(target)}
{}

bool StringExcluderDecorator::startReportOn(
	Component const & component,
	unsigned const depth
) {
	bool isMatch = component.name().find(_target) != std::string::npos;
	if (isMatch) {
		return false;
	}
	return AugmentedReporterDecorator::startReportOn(component, depth);
}

void StringExcluderDecorator::finishReportOn(
	Component const & component,
	unsigned const depth,
	Outcome const outcome
) {
	AugmentedReporterDecorator::finishReportOn(component, depth, outcome);
}

} // namespace luanics::testing::core
