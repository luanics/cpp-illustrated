#include "luanics/testing/core/StringMatcherDecorator.hpp"

namespace luanics::testing::core {

StringMatcherDecorator::StringMatcherDecorator(
	AugmentedReporter * decorated,
	MatchersByDepth matchers
) :
	AugmentedReporterDecorator{decorated},
	_matchers{std::move(matchers)}
{}

} // namespace luanics::testing::core
