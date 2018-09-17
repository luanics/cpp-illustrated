#pragma once

#include "luanics/testing/core/Outcome.hpp"
#include "luanics/testing/core/Reporter.hpp"

#include <stack>

namespace luanics::testing::core {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class AbstractReporter
///
/// @brief Skeleton version of Reporter that adds "depth" and "outcome".
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class AbstractReporter : public Reporter {
public:
	AbstractReporter() = default;

	/// @return false if wants to skip this component
	virtual bool startReportOn(Component const & component) override final;
	virtual void finishReportOn(Component const & component) override final;

	virtual void report(Error const & error) override final;
	virtual void report(Log const & log) override final;
	virtual void report(Result const & result) override final;

protected:
	std::size_t depth() const;

private:
	virtual bool doStartReportOn(Component const & component) = 0;
	virtual void doFinishReportOn(Component const & component, Outcome const outcome) = 0;

	virtual void doReport(Error const & error) = 0;
	virtual void doReport(Log const & log) = 0;
	virtual void doReport(Result const & result) = 0;

	std::stack<Outcome> _outcomes;
}; // class AbstractReporter

} // namespace luanics::testing::core
