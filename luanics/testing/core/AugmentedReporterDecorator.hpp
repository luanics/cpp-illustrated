#pragma once

#include "luanics/testing/core/AugmentedReporter.hpp"

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class AugmentedReporterDecorator
///
/// @brief Decorator pattern applied to AugmentedReporter.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class AugmentedReporterDecorator : public AugmentedReporter {
public:
	AugmentedReporterDecorator(AugmentedReporter * decorated);

	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) override;
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) override;

	virtual void report(Error const & error) override;
	virtual void report(Log const & log) override;
	virtual void report(Result const & result) override;

private:
	AugmentedReporter * _decorated;
}; // class AugmentedReporterDecorator

} // namespace luanics::testing::core
