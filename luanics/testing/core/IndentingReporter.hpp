#pragma once

#include "luanics/testing/core/AugmentedReporter.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class IndentingReporter
///
/// @brief Writes test results to ostream, indenting each level of hierarchy.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class IndentingReporter : public AugmentedReporter {
public:
	IndentingReporter(
		std::ostream * out,
		bool const isVerbose = true
	);

	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) override final;
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) override final;

	virtual void report(Error const & error) override final;
	virtual void report(Log const & log) override final;
	virtual void report(Result const & result) override final;

private:
	void pushLineIndex();
	unsigned popLineIndex();

	void setup();

	void composeLine(std::string const & name, core::Outcome const outcome);
	void composeLine(Error const & error);
	void composeLine(Log const & log);
	void composeLine(Result const & result);
	void composeFileLineIdentifier(char const * const filePath, int const line);
	void composeIndentation(unsigned const depth);
	void storeComposedLine();
	void storeComposedLineAt(unsigned const index);
	void clearLine();
	void flushLines();

	bool _isVerbose;
	unsigned _depth;
	std::vector<std::string> _lines;
	std::vector<unsigned> _indices;
	std::ostringstream _line;
	std::ostream * _out;

	std::string _noneIntro;
	std::string _logIntro;
	std::string _passIntro;
	std::string _failIntro;
	std::string _errorIntro;
}; // class IndentingReporter

} // namespace luanics::testing::core
