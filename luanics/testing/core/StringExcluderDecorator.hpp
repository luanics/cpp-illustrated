#pragma once

#include "luanics/testing/core/AugmentedReporterDecorator.hpp"

namespace luanics::testing::core {

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class StringExcluderDecorator
///
/// @brief Excludes any Components with target string in their name().
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class StringExcluderDecorator : public AugmentedReporterDecorator {
public:
	StringExcluderDecorator(
		AugmentedReporter * filtered,
		std::string target
	);

	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) final;
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) final;

private:
	std::string _target;
};

} // namespace luanics::testing::core
