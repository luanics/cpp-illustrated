#include "luanics/grid/DynamicGrid.hpp"

#include "luanics/logging/Contract.hpp"
#include "luanics/utility/Reverse.hpp"

#include <algorithm>
#include <iostream>

namespace luanics::grid {

DynamicGrid::DynamicGrid() :
	_width{0},
	_height{0},
	_data{}
{}

DynamicGrid::DynamicGrid(unsigned const width, unsigned const height) :
	_width{width},
	_height{height},
	_data(height, std::vector<char>(width, EmptyValue))
{}

unsigned DynamicGrid::width() const {
	return _width;
}

unsigned DynamicGrid::height() const {
	return _height;
}

DynamicGrid::ValueType & DynamicGrid::operator()(unsigned const x, unsigned const y) {
	return const_cast<char&>(const_cast<DynamicGrid const &>(*this).operator()(x,y));
}

DynamicGrid::ValueType const & DynamicGrid::operator()(unsigned const x, unsigned const y) const {
	EXPECTS(x < _width and y < _height);
	return _data[y][x];
}

void DynamicGrid::clear() {
	fillWith(EmptyValue);
}

void DynamicGrid::fillWith(ValueType const value) {
	for (auto & row: _data) {
		row.assign(_width, value);
	}
}

void DynamicGrid::writeTo(std::ostream & out) const {
	for (auto const & row : reverse(_data)) {
		for (auto const & value: row) {
			out << value;
		}
		out << std::endl;
	}
}

void DynamicGrid::readFrom(std::istream & in) {
	_data.clear();
	std::string line;
	std::size_t maxWidth = 0;
	while (std::getline(in, line)) {
		maxWidth = std::max(line.size(), maxWidth);
		_data.push_back(std::vector<char>(line.begin(), line.end()));
	}
	_width = maxWidth;
	_height = _data.size();
	for (auto & row: _data) {
		row.resize(_width, EmptyValue);
	}
	std::reverse(_data.begin(), _data.end());
}

} // namespace luanics::grid
