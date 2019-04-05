#include "luanics/grid/FlippedGrid.hpp"

#include "luanics/logging/Contract.hpp"
#include "luanics/testing/tutorial/Macros.hpp"

namespace luanics::grid {

FlippedGrid::FlippedGrid(std::unique_ptr<Grid> decorated) :
	_decorated{std::move(decorated)}
{}

unsigned FlippedGrid::width() const {
	FIX(return 0;)
}

unsigned FlippedGrid::height() const {
	FIX(return 0;)
}

FlippedGrid::ValueType & FlippedGrid::operator()(unsigned const x, unsigned const y) {
	FIX(
		static ValueType temp;
		return temp;
	)
}

FlippedGrid::ValueType const & FlippedGrid::operator()(unsigned const x, unsigned const y) const {
	FIX(
		static ValueType temp;
		return temp;
	)
}

void FlippedGrid::clear() {
	CREATE
}

void FlippedGrid::fillWith(ValueType const value) {
	CREATE
}

void FlippedGrid::writeTo(std::ostream & out) const {
	CREATE
}

void FlippedGrid::readFrom(std::istream & in) {
	CREATE
}

} // namespace luanics::grid
