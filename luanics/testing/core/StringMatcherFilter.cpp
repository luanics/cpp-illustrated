#include "luanics/testing/core/StringMatcherFilter.hpp"

namespace luanics::testing::core {

StringMatcherFilter::StringMatcherFilter(
	AugmentedReporter * filtered,
	MatchersByDepth matchers
) :
	AugmentedReporterDecorator{filtered},
	_matchers{std::move(matchers)}
{}

} // namespace luanics::testing::core
