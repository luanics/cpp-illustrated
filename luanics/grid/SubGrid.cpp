#include "luanics/grid/SubGrid.hpp"

#include "luanics/logging/Contract.hpp"

namespace luanics::grid {

SubGrid::SubGrid(
	unsigned const width,
	unsigned const height,
	unsigned const xOffset,
	unsigned const yOffset,
	Grid * parent
) :
	_width{width},
	_height{height},
	_xOffset{xOffset},
	_yOffset{yOffset},
	_parent{parent}
{
	EXPECTS(width + xOffset <= parent->width());
	EXPECTS(height + yOffset <= parent->height());
}

unsigned SubGrid::xOffset() const {
	return _xOffset;
}

unsigned SubGrid::yOffset() const {
	return _yOffset;
}

unsigned SubGrid::width() const {
	return _width;
}

unsigned SubGrid::height() const {
	return _height;
}

Grid::ValueType & SubGrid::operator()(unsigned const x, unsigned const y) {
	return const_cast<char&>(const_cast<SubGrid const &>(*this).operator()(x,y));
}

Grid::ValueType const & SubGrid::operator()(unsigned const x, unsigned const y) const {
	EXPECTS(x < _width and y < _height);
	return _parent->operator()(x + _xOffset, y + _yOffset);
}

void SubGrid::clear() {
	fillWith(EmptyValue);
}

void SubGrid::fillWith(ValueType const value) {
	for (unsigned x = 0; x < _width; ++x) {
		for (unsigned y = 0; y < _height; ++y) {
			operator()(x,y) = value;
		}
	}
}

void SubGrid::writeTo(std::ostream & out) const {
	Grid::writeTo(out);
}

void SubGrid::readFrom(std::istream & in) {
	Grid::readFrom(in);
}

} // namespace luanics::grid
