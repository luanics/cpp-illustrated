#pragma once

#include "luanics/testing/core/Outcome.hpp"
#include "luanics/testing/core/Reporter.hpp"

#include <stack>

namespace luanics::testing::core {

class AugmentedReporter;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class ReporterAugmenter
///
/// @brief Adapts Reporter interface to the AugmentedReporter interface.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class ReporterAugmenter : public Reporter {
public:
	ReporterAugmenter(AugmentedReporter * adapted);

	virtual bool startReportOn(Component const & component) override final;
	virtual void finishReportOn(Component const & component) override final;

	virtual void report(Error const & error) override final;
	virtual void report(Log const & log) override final;
	virtual void report(Result const & result) override final;

private:
	unsigned depth() const;

	AugmentedReporter * _adapted;
	std::stack<Outcome> _outcomes;
}; // class ReporterAugmenter

} // namespace luanics::testing::core
