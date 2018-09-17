#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/unit/Reporter.hpp"
#include "luanics/testing/unit/ReporterAdapter.hpp"

#include <cassert>

namespace luanics {
namespace testing {
namespace unit {

ReporterAdapter::ReporterAdapter(unit::Reporter * adapted) :
	_adapted{adapted}
{}

Level ReporterAdapter::level() const {
	LUANICS_ASSERT(depth() <= static_cast<std::underlying_type_t<Level>>(Level::TEST));
	return static_cast<Level>(depth());
}

bool ReporterAdapter::doStartReportOn(core::Component const & component) {
	switch (level()) {
		case Level::SUITE: return _adapted->startTestSuite();
		case Level::SET: return _adapted->startTestSet(component.name());
		case Level::TEST: return _adapted->startTest(component.name());
		default: assert(false); return false;
	}
}

void ReporterAdapter::doFinishReportOn(core::Component const & component, core::Outcome const outcome) {
	switch (level()) {
		case Level::SUITE: _adapted->finishTestSuite(outcome); break;
		case Level::SET: _adapted->finishTestSet(component.name(), outcome); break;
		case Level::TEST: _adapted->finishTest(component.name(), outcome); break;
		default: assert(false); break;
	}
}

void ReporterAdapter::doReport(core::Error const & error) {
	_adapted->report(error);
}

void ReporterAdapter::doReport(core::Log const & log) {
	_adapted->report(log);
}

void ReporterAdapter::doReport(core::Result const & result) {
	_adapted->report(result);
}

} // namespace unit
} // namespace testing
} // namespace luanics
