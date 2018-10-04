#pragma once

#include "luanics/string/Matcher.hpp"
#include "luanics/testing/core/AugmentedReporterDecorator.hpp"

#include <memory>
#include <unordered_map>

namespace luanics::testing::core {

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class StringMatcherFilter
///
/// @brief AugmentedReporterDecorator that only reports on Components with matching name().
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class StringMatcherFilter : public AugmentedReporterDecorator {
public:
	using MatchersByDepth = std::unordered_map<
		unsigned,
		std::unique_ptr<string::Matcher>
	>;

	StringMatcherFilter(
		AugmentedReporter * filtered,
		MatchersByDepth matchers
	);

private:
	MatchersByDepth _matchers;
};

} // namespace luanics::testing::core
