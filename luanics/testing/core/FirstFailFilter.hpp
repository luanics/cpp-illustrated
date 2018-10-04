#pragma once

#include "luanics/testing/core/AugmentedReporterDecorator.hpp"

namespace luanics::testing::core {

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class FirstFailFilter
///
/// @brief AugmentedReporterDecorator that stops reporting after the
///   first FAIL or ERROR Outcome.
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class FirstFailFilter : public AugmentedReporterDecorator {
public:
	FirstFailFilter(AugmentedReporter * filtered);

	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) override final;
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) override final;

private:
	bool _hasFailed;
};

} // namespace luanics::testing::core
