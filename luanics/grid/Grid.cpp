#include "luanics/grid/Grid.hpp"

#include <iostream>

namespace luanics::grid {

constexpr char Grid::EmptyValue;

void Grid::writeTo(std::ostream & out) const {
	for (unsigned y = height() - 1; y < height(); --y) {
		for (unsigned x = 0; x < width(); ++x) {
			out << operator()(x, y);
		}
		out << std::endl;
	}
}

void Grid::readFrom(std::istream & in) {
	// Don't resize to fit input. Just set failbit and quit if input doesn't match width.
	std::string line;
	unsigned y = height() - 1;
	while ((y < height()) and std::getline(in, line)) {
		auto const width = line.size();
		if (width != this->width()) {
			in.setstate(std::ios::failbit);
			return;
		}
		for (unsigned x = 0; x < this->width(); ++x) {
			operator()(x,y) = line[x];
		}
		--y;
	}
	bool isComplete = y == height();
	if (not isComplete) {
		in.setstate(std::ios::failbit);
	}
}

std::ostream & operator<<(std::ostream & out, Grid const & grid) {
	grid.writeTo(out);
	return out;
}

std::istream & operator>>(std::istream & in, Grid & grid) {
	grid.readFrom(in);
	return in;
}

} // namespace luanics::grid
