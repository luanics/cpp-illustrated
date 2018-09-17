#pragma once

#include "luanics/testing/tutorial/Level.hpp"
#include "luanics/testing/tutorial/Reporter.hpp"

#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

namespace luanics::testing::tutorial {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class StandardReporter
///
/// @brief The go-to reporter for tutorials.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class StandardReporter : public Reporter {
public:
	StandardReporter(
		std::ostream * out,
		bool const isUsingColor = true,
		bool const isVerbose = true
	);

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
	void pushLineIndex();
	unsigned popLineIndex();

	void setupUsingAnsiColors();
	void setupUsingNoColors();

	void composeLine(std::string const & name, core::Outcome const outcome);
	void composeLine(core::Error const & error);
	void composeLine(core::Log const & log);
	void composeLine(core::Result const & result);
	void composeFileLineIdentifier(char const * const filePath, int const line);
	void composeIndentation(Level const level);
	void storeComposedLine();
	void storeComposedLineAt(unsigned const index);
	void clearLine();
	void flushLines();

	bool _isVerbose;
	Level _level;
	std::vector<std::string> _lines;
	std::vector<unsigned> _indices;
	std::ostringstream _line;
	std::ostream * _out;

	std::string _noneIntro;
	std::string _logIntro;
	std::string _passIntro;
	std::string _failIntro;
	std::string _errorIntro;
};

} // luanics::testing::tutorial
