#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Component.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/IndentingReporter.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/utility/Ansi.hpp"
#include "luanics/utility/Paths.hpp"
#include "luanics/utility/Streams.hpp"

#include <algorithm>
#include <iterator>

namespace luanics::testing::core {

namespace {

std::string const INTRO_BEGIN_DELIMITER = "[";
std::string const INTRO_END_DELIMITER = "]";
std::string const INDENT = "   ";

}

IndentingReporter::IndentingReporter(
	std::ostream * out,
	bool const isUsingColor,
	bool const isVerbose
) :
	_isVerbose{isVerbose},
	_depth{0},
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

bool IndentingReporter::startReportOn(Component const & component, unsigned const depth) {
	_depth = depth;
	pushLineIndex();
	return true;
}

void IndentingReporter::finishReportOn(Component const & component, unsigned const depth, Outcome const outcome) {
	_depth = depth;
	composeLine(component.name(), outcome);
	storeComposedLineAt(popLineIndex());
	if (depth == 0) {
		flushLines();
	}
}

void IndentingReporter::report(core::Error const & error) {
	composeLine(error);
	storeComposedLine();
}

void IndentingReporter::report(core::Log const & log) {
	composeLine(log);
	storeComposedLine();
}

void IndentingReporter::report(core::Result const & result) {
	composeLine(result);
	storeComposedLine();
}

void IndentingReporter::setupUsingAnsiColors() {
	using namespace utility::ansi;
	_noneIntro = INTRO_BEGIN_DELIMITER + DARK_GRAY + "NONE " + RESET + INTRO_END_DELIMITER;
	_logIntro = INTRO_BEGIN_DELIMITER + LIGHT_GRAY + "LOG  " + RESET + INTRO_END_DELIMITER;
	_passIntro = INTRO_BEGIN_DELIMITER + GREEN + "PASS " + RESET + INTRO_END_DELIMITER;
	_failIntro = INTRO_BEGIN_DELIMITER + RED + "FAIL " + RESET + INTRO_END_DELIMITER;
	_errorIntro = INTRO_BEGIN_DELIMITER + BOLD_RED + "ERROR" + RESET + INTRO_END_DELIMITER;
}

void IndentingReporter::setupUsingNoColors() {
	_noneIntro = INTRO_BEGIN_DELIMITER + "NONE " + INTRO_END_DELIMITER;
	_logIntro = INTRO_BEGIN_DELIMITER + "LOG  " + INTRO_END_DELIMITER;
	_passIntro = INTRO_BEGIN_DELIMITER + "PASS " + INTRO_END_DELIMITER;
	_failIntro = INTRO_BEGIN_DELIMITER + "FAIL " + INTRO_END_DELIMITER;
	_errorIntro = INTRO_BEGIN_DELIMITER + "ERROR" + INTRO_END_DELIMITER;
}

void IndentingReporter::composeLine(std::string const & name, core::Outcome const outcome) {
	composeIndentation(_depth);
	switch (outcome) {
		case core::Outcome::NONE: _line << _noneIntro; break;
		case core::Outcome::PASS: _line << _passIntro; break;
		case core::Outcome::FAIL: _line << _failIntro; break;
		case core::Outcome::ERROR: _line << _errorIntro; break;
	}
	_line << " " << name;
}

void IndentingReporter::composeLine(core::Error const & error) {
	composeIndentation(_depth + 1);
	_line << _errorIntro;
	_line << " - " << error.message;
}

void IndentingReporter::composeLine(core::Log const & log) {
	composeIndentation(_depth + 1);
	_line << _logIntro;
	_line << " ";
	composeFileLineIdentifier(log.fileName, log.line);
	_line << " - " << log.message;
}

void IndentingReporter::composeLine(core::Result const & result) {
	composeIndentation(_depth + 1);
	_line << (result.isPass ? _passIntro : _failIntro);
	_line << " ";
	composeFileLineIdentifier(result.fileName, result.line);
	if (_isVerbose) {
		_line << " - " << result.message;
	}
}

void IndentingReporter::composeFileLineIdentifier(char const * const filePath, int const line) {
	_line << utility::fileNameFrom(filePath) << ":" << line;
}

void IndentingReporter::composeIndentation(unsigned const depth) {
	for (unsigned d{0}; d < depth; ++d) {
		_line << INDENT;
	}
}

void IndentingReporter::storeComposedLine() {
	_lines.push_back(_line.str());
	clearLine();
}

void IndentingReporter::storeComposedLineAt(unsigned const index) {
	_lines[index] = _line.str();
	clearLine();
}

void IndentingReporter::clearLine() {
	_line.str("");
	_line.clear();
}

void IndentingReporter::flushLines() {
	std::copy(
		_lines.begin(),
		_lines.end(),
		std::ostream_iterator<std::string>(*_out, "\n")
	);
}

void IndentingReporter::pushLineIndex() {
	_lines.push_back("");
	_indices.push_back(_lines.size() - 1);
}

unsigned IndentingReporter::popLineIndex() {
	auto const result = _indices.back();
	_indices.pop_back();
	return result;
}

} // namespace luanics::testing::core
