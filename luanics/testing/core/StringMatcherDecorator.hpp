#pragma once

#include "luanics/string/Matcher.hpp"
#include "luanics/testing/core/AugmentedReporterDecorator.hpp"

#include <memory>
#include <unordered_map>

namespace luanics::testing::core {

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class StringMatcherDecorator
///
/// @brief Only reports on Components with matching name().
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class StringMatcherDecorator : public AugmentedReporterDecorator {
public:
	using MatchersByDepth = std::unordered_map<
		unsigned,
		std::unique_ptr<string::Matcher>
	>;

	StringMatcherDecorator(
		AugmentedReporter * decorated,
		MatchersByDepth matchers
	);

private:
	MatchersByDepth _matchers;
};

} // namespace luanics::testing::core
