#pragma once

#include "luanics/testing/core/AbstractReporter.hpp"
#include "luanics/testing/tutorial/Level.hpp"
#include "luanics/testing/tutorial/Reporter.hpp"

namespace luanics::testing::tutorial {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class ReporterAdapter
///
/// @brief An core::AbstractReporter that drives a tutorial::Reporter.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ReporterAdapter : public core::AbstractReporter {
public:
	ReporterAdapter(tutorial::Reporter * adapted);

private:
	Level level() const;

	virtual bool doStartReportOn(core::Component const & component) override final;
	virtual void doFinishReportOn(core::Component const & component, core::Outcome const outcome) override final;

	virtual void doReport(core::Error const & error) override final;
	virtual void doReport(core::Log const & log) override final;
	virtual void doReport(core::Result const & result) override final;

	tutorial::Reporter * _adapted;
}; // class ReporterAdapter

} // namespace luanics::testing::tutorial
