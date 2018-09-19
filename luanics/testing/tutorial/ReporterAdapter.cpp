#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/tutorial/ReporterAdapter.hpp"

#include <cassert>

namespace luanics::testing::tutorial {

ReporterAdapter::ReporterAdapter(tutorial::Reporter * adapted) :
	_adapted{adapted}
{}

Level ReporterAdapter::level() const {
	LUANICS_ASSERT(depth() <= toUnderlyingType(Level::SECTION));
	return static_cast<Level>(depth());
}

bool ReporterAdapter::doStartReportOn(core::Component const & component) {
	switch (level()) {
		case Level::TUTORIAL: return _adapted->startTutorial();
		case Level::PART: return _adapted->startPart(component.name());
		case Level::CHAPTER: return _adapted->startChapter(component.name());
		case Level::SECTION: return _adapted->startSection(component.name());
		default: LUANICS_NEVER_REACHED(toUnderlyingType(level())); return false;
	}
}

void ReporterAdapter::doFinishReportOn(core::Component const & component, core::Outcome const outcome) {
	switch (level()) {
		case Level::TUTORIAL: _adapted->finishTutorial(outcome); break;
		case Level::PART: _adapted->finishPart(component.name(), outcome); break;
		case Level::CHAPTER: _adapted->finishChapter(component.name(), outcome); break;
		case Level::SECTION: _adapted->finishSection(component.name(), outcome); break;
		default: LUANICS_NEVER_REACHED(toUnderlyingType(level()));
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

} // namespace luanics::testing::tutorial
