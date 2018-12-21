#include "luanics/cards/PaintHelpers.hpp"
#include "luanics/container/FlippedGrid.hpp"
#include "luanics/graphics/Brush.hpp"
#include "luanics/graphics/Line.hpp"
#include "luanics/graphics/Offset.hpp"
#include "luanics/graphics/Painter.hpp"
#include "luanics/graphics/Point.hpp"

namespace luanics {
namespace cards {

void paintFrame(
	luanics::graphics::Offset const & cardSize,
	luanics::graphics::Point const & topLeft,
	FlippedGrid & grid
) {
	using Brush = luanics::graphics::Brush;
	using Line = luanics::graphics::Line;
	using Offset = luanics::graphics::Offset;
	using Painter = luanics::graphics::Painter;
	using Point = luanics::graphics::Point;

	Painter painter{&grid};

	Point const topRight{topLeft.x() + cardSize.x() + 2, topLeft.y()};
	Point const bottomLeft{topLeft.x(), topLeft.y() + cardSize.y() + 2};
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
