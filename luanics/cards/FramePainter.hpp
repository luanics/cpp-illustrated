#pragma once

#include "luanics/graphics/Offset.hpp"

namespace luanics {
	namespace graphics { class Point; }
	class FlippedGrid;
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class FramePainter
///
/// @brief Paints a frame around bottom card in a pile.
///
/// Open on the bottom. Looks like this:
///        _____
///       |     |
///       |     |
///       |     |
///       |     |
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class FramePainter {
public:
	using Offset = luanics::graphics::Offset;
	using Point = luanics::graphics::Point;

	FramePainter(Offset const & cardSize);

	Offset const & cardSize() const;
	void paint(Point const & topLeft, FlippedGrid & grid) const;

private:
	Offset _cardSize;
}; // class FramePainter

} // namespace cards
} // namespace luanics
