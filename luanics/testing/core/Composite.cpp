#include "luanics/testing/core/Composite.hpp"
#include "luanics/testing/core/Reporter.hpp"

namespace luanics::testing::core {

Composite::Composite(std::string name) :
	_name{std::move(name)},
	_children{}
{}

std::string const & Composite::name() const {
	return _name;
}

void Composite::run(Reporter & reporter) {
	if (not reporter.startReportOn(*this)) return;
	for (Component * child: _children) {
		child->run(reporter);
	}
	reporter.finishReportOn(*this);
}

void Composite::add(Component * child) {
	_children.push_back(child);
}

typename Composite::ChildMapType const & Composite::children() const {
	return _children;
}

} // namespace luanics::testing::core
