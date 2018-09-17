#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/core/SimpleReporter.hpp"

namespace luanics::testing::core {

SimpleReporter::SimpleReporter() :
	_numPassResults{0}, _numFailResults{0}, _numErrors{0}, _numLogs{0}
{}

bool SimpleReporter::startReportOn(Component const & component) {
	return true;
}

void SimpleReporter::finishReportOn(Component const & component) {

}

void SimpleReporter::report(Result const & result) {
	if (result.isPass) {
		++_numPassResults;
	}
	else {
		++_numFailResults;
	}
}

void SimpleReporter::report(Error const & error) {
	++_numErrors;
}

void SimpleReporter::report(Log const & log) {
	++_numLogs;
}

std::size_t SimpleReporter::numPassResults() const {
	return _numPassResults;
}

std::size_t SimpleReporter::numFailResults() const {
	return _numFailResults;
}

std::size_t SimpleReporter::numErrors() const {
	return _numErrors;
}

size_t SimpleReporter::numLogs() const {
	return _numLogs;
}

} // namespace luanics::testing::core
