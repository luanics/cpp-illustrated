#pragma once

#include "luanics/grid/Grid.hpp"

namespace luanics::grid {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class SubGrid
///
/// @brief Grid that refers to a region in a "parent" Grid.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SubGrid : public Grid {
public:
	SubGrid(
		unsigned const width,
		unsigned const height,
		unsigned const xOffset,
		unsigned const yOffset,
		Grid * parent
	);

	unsigned xOffset() const;
	unsigned yOffset() const;

	virtual unsigned width() const final;
	virtual unsigned height() const final;
	/// @pre x < width and y < height
	virtual ValueType & operator()(unsigned const x, unsigned const y) final;
	/// @pre x < width and y < height
	virtual ValueType const & operator()(unsigned const x, unsigned const y) const final;
	virtual void clear() final;
	virtual void fillWith(ValueType const value) final;
	virtual void writeTo(std::ostream & out) const final;
	virtual void readFrom(std::istream & in) final;

private:
	unsigned _width;
	unsigned _height;
	unsigned _xOffset;
	unsigned _yOffset;
	Grid * _parent;
};
// class SubGrid

} // namespace luanics::grid
