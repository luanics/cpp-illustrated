#pragma once

#include "luanics/cards/Card.hpp"
#include "luanics/graphics/Brush.hpp"
#include "luanics/graphics/Offset.hpp"
#include "luanics/graphics/Point.hpp"

namespace luanics {
	class FlippedGrid;
	namespace graphics { class Point; }
namespace cards {
	class Card;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class CardPainter
///
/// @brief Draws a card face up or face down using a graphics::Painter.
///
///     Face up like this:            Face down like this:
///
///          *******                       *******
/// (name)-> *2H  r* <-(color)             *@@@@@*
///          *     *                       *@@@@@*
///          *     *                       *@@@@@*
///          *     *                       *@@@@@*
///          *******                       *******
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class CardPainter {
public:
	using Brush = luanics::graphics::Brush;
	using Offset = luanics::graphics::Offset;
	using Painter = luanics::graphics::Painter;
	using Point = luanics::graphics::Point;

	CardPainter(); ///< Default card style
	/// @pre cardSize.x() > 0 and cardSize.y() > 0
	/// @pre nameOffset.x() >= 0 and nameOffset.y() >= 0
	/// @pre colorOffset.x() >=0 and colorOffset.y() >= 0
	CardPainter(
		Brush const & faceUpBrush,
		Brush const & faceDownBrush,
		Offset const & cardSize,
		Offset const & nameOffset,
		Offset const & colorOffset
	);

	Offset const & cardSize() const;
	void paintFaceUp(
		Point const & topLeft,
		Card const & card,
		FlippedGrid & grid
	) const;
	void paintFaceDown(
		Point const & topLeft,
		Card const & card,
		FlippedGrid & grid
	) const;
	void paintSpace(
		Point const & topLeft,
		FlippedGrid & grid
	) const;

private:
	Brush _faceUpBrush;
	Brush _faceDownBrush;
	Offset _cardSize;
	Offset _nameOffset;
	Offset _colorOffset;
}; // class CardPainter

} // namespace cards
} // namespace luanics
