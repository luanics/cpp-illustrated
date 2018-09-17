#pragma once

#include "luanics/testing/tutorial/Reporter.hpp"

#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

namespace luanics::testing::tutorial {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class FirstFailFilter
///
/// @brief Reporter that stops reporting after first failed Outcome.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class FirstFailFilter : public Reporter {
public:
	FirstFailFilter(Reporter * filtered);

	virtual bool startTutorial() override final;
	virtual void finishTutorial(core::Outcome const outcome) override final;
	virtual bool startPart(std::string const & name) override final;
	virtual void finishPart(std::string const & name, core::Outcome const outcome) override final;
	virtual bool startChapter(std::string const & name) override final;
	virtual void finishChapter(std::string const & name, core::Outcome const outcome) override final;
	virtual bool startSection(std::string const & name) override final;
	virtual void finishSection(std::string const & name, core::Outcome const outcome) override final;

	virtual void report(core::Error const & error) override final;
	virtual void report(core::Log const & log) override final;
	virtual void report(core::Result const & result) override final;

private:
	Reporter * _filtered;
	bool _hasFailed;
};

} // namespace luanics::testing::tutorial
