#pragma once

#include "luanics/testing/core/Outcome.hpp"

#include <string>

namespace luanics::testing {

namespace core {
	class Error;
	class Log;
	class Result;
}

namespace tutorial {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Reporter
///
/// @brief Reporter tailored to the structure of tutorials.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Reporter {
public:

	virtual ~Reporter() = default;

	//////////////////////////////////////////////////////////////////
	/// @name Test Components
	//////////////////////////////////////////////////////////////////
	//@{
	virtual bool startTutorial() = 0;
	virtual void finishTutorial(core::Outcome const outcome) = 0;

	virtual bool startPart(std::string const & name) = 0;
	virtual void finishPart(std::string const & name, core::Outcome const outcome) = 0;

	virtual bool startChapter(std::string const & name) = 0;
	virtual void finishChapter(std::string const & name, core::Outcome const outcome) = 0;

	virtual bool startSection(std::string const & name) = 0;
	virtual void finishSection(std::string const & name, core::Outcome const outcome) = 0;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Test Statements
	//////////////////////////////////////////////////////////////////
	//@{
	virtual void report(core::Error const & error) = 0;
	virtual void report(core::Log const & log) = 0;
	virtual void report(core::Result const & result) = 0;
	//@}

}; // class Reporter

} // namespace tutorial
} // namespace luanics::testing
