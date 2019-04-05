#pragma once

#include "luanics/grid/Grid.hpp"

#include <memory>

namespace luanics::grid {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class FlippedGrid
///
/// @brief A Grid that reverses the direction of Y axis.
///
/// Flipped grid has origin (0,0) at top left.
///
/// *----> x
/// |
/// |
/// V y
///
/// Implemented as a Grid Decorator. When it wraps a regular grid
///   (origin at bottom left), the result is origin at top left.
///   Note that the orientation of the axes is not observable until
///   IO is used.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class FlippedGrid : public Grid {
public:
	FlippedGrid(std::unique_ptr<Grid> decorated);

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
	std::unique_ptr<Grid> _decorated;
}; // class FlippedGrid

} // namespace luanics::grid
