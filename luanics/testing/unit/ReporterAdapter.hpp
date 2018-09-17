#pragma once

#include "luanics/testing/core/AbstractReporter.hpp"
#include "luanics/testing/unit/Level.hpp"

namespace luanics::testing::unit {

class Reporter;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class ReporterAdapter
///
/// @brief A core::Reporter that drives a unit::Reporter.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ReporterAdapter : public core::AbstractReporter {
public:
	ReporterAdapter(unit::Reporter * adapted);

private:
	Level level() const;

	virtual bool doStartReportOn(core::Component const & component) override final;
	virtual void doFinishReportOn(core::Component const & component, core::Outcome const outcome) override final;

	virtual void doReport(core::Error const & error) override final;
	virtual void doReport(core::Log const & log) override final;
	virtual void doReport(core::Result const & result) override final;

	unit::Reporter * _adapted;
}; // class ReporterAdapter

} // namespace luanics::testing::unit
