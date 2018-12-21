#include "luanics/cards/FramePainter.hpp"
#include "luanics/graphics/Brush.hpp"
#include "luanics/graphics/Line.hpp"
#include "luanics/graphics/Painter.hpp"

namespace luanics {
namespace cards {

FramePainter::FramePainter(Offset const & cardSize) :
	_cardSize{cardSize}
{}

FramePainter::Offset const & FramePainter::cardSize() const {
	return _cardSize;
}

void FramePainter::paint(
	Point const & topLeft,
	FlippedGrid & grid
) const {
	using Brush = luanics::graphics::Brush;
	using Line = luanics::graphics::Line;
	using Painter = luanics::graphics::Painter;

	Painter painter{&grid};

	Point const topRight{topLeft.x() + _cardSize.x() + 2, topLeft.y()};
	Point const bottomLeft{topLeft.x(), topLeft.y() + _cardSize.y() + 2};
	Point const bottomRight{topRight.x(), bottomLeft.y()};

	// Paint vertical side lines
	Brush const verticalBrush{'|'};
	painter.setBrush(verticalBrush);
	Line const leftLine{topLeft, bottomLeft};
	painter.paint(leftLine);
	Line const rightLine{topRight, bottomRight};
	painter.paint(rightLine);

	// Paint top line in top row
	Brush const horizontalBrush{'_'};
	painter.setBrush(horizontalBrush);
	Line const horizontalLine{topLeft + Offset{1,0}, topRight - Offset{1,0}};
	painter.paint(horizontalLine);
}

} // namespace cards
} // namespace luanics
