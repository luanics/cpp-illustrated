#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Leaf.hpp"
#include "luanics/testing/core/Reporter.hpp"

#include <iostream>

namespace luanics::testing::core {

Leaf::Leaf(std::string name) :
	_name{std::move(name)}
{}

std::string const & Leaf::name() const {
	return _name;
}

void Leaf::run(Reporter & reporter) {
	if (not reporter.startReportOn(*this)) return;
	try {
		doRun(reporter);
	}
	catch (std::exception const & error) {
		reporter.report(Error{error.what()});
	}
	reporter.finishReportOn(*this);
}

} // namespace luanics::testing::core
