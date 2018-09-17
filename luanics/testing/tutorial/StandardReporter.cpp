#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/tutorial/StandardReporter.hpp"
#include "luanics/utility/Ansi.hpp"
#include "luanics/utility/Paths.hpp"
#include "luanics/utility/Streams.hpp"

#include <algorithm>
#include <iterator>

namespace luanics::testing::tutorial {

namespace {

std::string const INTRO_BEGIN_DELIMITER = "[";
std::string const INTRO_END_DELIMITER = "]";
std::string const INDENT = "   ";

Level incremented(Level level) {
	return ++level;
}

}

StandardReporter::StandardReporter(
	std::ostream * out,
	bool const isUsingColor,
	bool const isVerbose
) :
	_isVerbose{isVerbose},
	_level{Level::TUTORIAL},
	_lines{},
	_indices{},
	_line{},
	_out{out},
	_noneIntro{},
	_logIntro{},
	_passIntro{},
	_failIntro{},
	_errorIntro{}
{
	if (isUsingColor) {
		setupUsingAnsiColors();
	}
	else {
		setupUsingNoColors();
	}
}

bool StandardReporter::startTutorial() {
	_level = Level::TUTORIAL;
	pushLineIndex();
	return true;
}

void StandardReporter::finishTutorial(core::Outcome const outcome) {
	_level = Level::TUTORIAL;
	composeLine("Tutorial", outcome);
	storeComposedLineAt(popLineIndex());
	flushLines();
}

bool StandardReporter::startPart(std::string const & name) {
	_level = Level::PART;
	pushLineIndex();
	return true;
}

void StandardReporter::finishPart(std::string const & name, core::Outcome const outcome) {
	_level = Level::PART;
	composeLine(name, outcome);
	storeComposedLineAt(popLineIndex());
}

bool StandardReporter::startChapter(std::string const & name) {
	_level = Level::CHAPTER;
	pushLineIndex();
	return true;
}

void StandardReporter::finishChapter(std::string const & name, core::Outcome const outcome) {
	_level = Level::CHAPTER;
	composeLine(name, outcome);
	storeComposedLineAt(popLineIndex());
}

bool StandardReporter::startSection(std::string const & name) {
	_level = Level::SECTION;
	pushLineIndex();
	return true;
}

void StandardReporter::finishSection(std::string const & name, core::Outcome const outcome) {
	_level = Level::SECTION;
	composeLine(name, outcome);
	storeComposedLineAt(popLineIndex());
}

void StandardReporter::report(core::Error const & error) {
	composeLine(error);
	storeComposedLine();
}

void StandardReporter::report(core::Log const & log) {
	composeLine(log);
	storeComposedLine();
}

void StandardReporter::report(core::Result const & result) {
	composeLine(result);
	storeComposedLine();
}

void StandardReporter::setupUsingAnsiColors() {
	using namespace utility::ansi;
	_noneIntro = INTRO_BEGIN_DELIMITER + DARK_GRAY + "NONE " + RESET + INTRO_END_DELIMITER;
	_logIntro = INTRO_BEGIN_DELIMITER + LIGHT_GRAY + "LOG  " + RESET + INTRO_END_DELIMITER;
	_passIntro = INTRO_BEGIN_DELIMITER + GREEN + "PASS " + RESET + INTRO_END_DELIMITER;
	_failIntro = INTRO_BEGIN_DELIMITER + RED + "FAIL " + RESET + INTRO_END_DELIMITER;
	_errorIntro = INTRO_BEGIN_DELIMITER + BOLD_RED + "ERROR" + RESET + INTRO_END_DELIMITER;
}

void StandardReporter::setupUsingNoColors() {
	_noneIntro = INTRO_BEGIN_DELIMITER + "NONE " + INTRO_END_DELIMITER;
	_logIntro = INTRO_BEGIN_DELIMITER + "LOG  " + INTRO_END_DELIMITER;
	_passIntro = INTRO_BEGIN_DELIMITER + "PASS " + INTRO_END_DELIMITER;
	_failIntro = INTRO_BEGIN_DELIMITER + "FAIL " + INTRO_END_DELIMITER;
	_errorIntro = INTRO_BEGIN_DELIMITER + "ERROR" + INTRO_END_DELIMITER;
}

void StandardReporter::composeLine(std::string const & name, core::Outcome const outcome) {
	composeIndentation(_level);
	switch (outcome) {
		case core::Outcome::NONE: _line << _noneIntro; break;
		case core::Outcome::PASS: _line << _passIntro; break;
		case core::Outcome::FAIL: _line << _failIntro; break;
		case core::Outcome::ERROR: _line << _errorIntro; break;
	}
	_line << " " << name;
}

void StandardReporter::composeLine(core::Error const & error) {
	composeIndentation(incremented(_level));
	_line << _errorIntro;
	_line << " - " << error.message;
}

void StandardReporter::composeLine(core::Log const & log) {
	composeIndentation(incremented(_level));
	_line << _logIntro;
	_line << " ";
	composeFileLineIdentifier(log.fileName, log.line);
	_line << " - " << log.message;
}

void StandardReporter::composeLine(core::Result const & result) {
	composeIndentation(_level);
	_line << (result.isPass ? _passIntro : _failIntro);
	_line << " ";
	composeFileLineIdentifier(result.fileName, result.line);
	if (_isVerbose) {
		_line << " - " << result.message;
	}
}

void StandardReporter::composeFileLineIdentifier(char const * const filePath, int const line) {
	_line << utility::fileNameFrom(filePath) << ":" << line;
}

void StandardReporter::composeIndentation(Level const level) {
	for (Level l = Level::TUTORIAL; l < level; ++l) {
		_line << INDENT;
	}
}

void StandardReporter::storeComposedLine() {
	_lines.push_back(_line.str());
	clearLine();
}

void StandardReporter::storeComposedLineAt(unsigned const index) {
	_lines[index] = _line.str();
	clearLine();
}

void StandardReporter::clearLine() {
	_line.str("");
	_line.clear();
}

void StandardReporter::flushLines() {
	std::copy(
		_lines.begin(),
		_lines.end(),
		std::ostream_iterator<std::string>(*_out, "\n")
	);
}

void StandardReporter::pushLineIndex() {
	_lines.push_back("");
	_indices.push_back(_lines.size() - 1);
}

unsigned StandardReporter::popLineIndex() {
	auto const result = _indices.back();
	_indices.pop_back();
	return result;
}

} // namespace luanics::testing::tutorial
