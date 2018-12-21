#include "luanics/cards/freecell/Cascade.hpp"
#include "luanics/cards/freecell/Cell.hpp"
#include "luanics/cards/freecell/Foundation.hpp"
#include "luanics/cards/freecell/Painter.hpp"
#include "luanics/cards/freecell/Model.hpp"
#include "luanics/cards/Painting.hpp"
#include "luanics/graphics/Line.hpp"
#include "luanics/graphics/Point.hpp"

#include <string>

#include "../../graphics/Offset.hpp"

namespace {

luanics::graphics::Offset const HORIZONTAL_SPACE{1, 0};
luanics::graphics::Offset const VERTICAL_SPACE{0,4};
luanics::graphics::Point const STARTING_POINT{2,2};

luanics::graphics::Point cellsStart(
	luanics::graphics::Point const & foundationsStart,
	luanics::graphics::Offset const & frameExtent,
	int const numFoundations
) {
	luanics::graphics::Offset const offsetPerFoundation{
		frameExtent.x() + HORIZONTAL_SPACE.x() + 1, 0
	};
	return
		foundationsStart
		+ numFoundations * offsetPerFoundation
		+ 2 * HORIZONTAL_SPACE * 2
	;
}

luanics::graphics::Point cascadesStart(
	luanics::graphics::Point const & foundationsStart,
	luanics::graphics::Offset const & frameExtent
) {
	return
		foundationsStart
		+ luanics::graphics::Offset{0, frameExtent.y()}
		+ VERTICAL_SPACE
	;
}

} // namespace

namespace luanics {
namespace cards {
namespace freecell {

Painter::Painter(
	luanics::graphics::Painter * inner,
	CardPaintSpec const & spec
) :
	_inner{inner},
	_spec{spec},
	_frameExtent{spec.bottomRight().x() + 2, spec.bottomRight().y() + 1},
	_foundationsStart{STARTING_POINT + luanics::graphics::Offset{2,2}},
	_cellsStart{cellsStart(_foundationsStart, _frameExtent, Model::NUM_FOUNDATIONS)},
	_cascadesStart{cascadesStart(_foundationsStart, _frameExtent)},
	_textStart{STARTING_POINT}
{}




void Painter::paintFrame(luanics::graphics::Point const & topLeft) {
	using luanics::graphics::Brush;
	using luanics::graphics::Offset;
	using luanics::graphics::Line;
	using luanics::graphics::Point;

	// Has this shape:
	// ___
	// | |
	// | |

	Point const topRight{topLeft.x() + _frameExtent.x(), topLeft.y()};
	Point const bottomLeft{topLeft.x(), topLeft.y() + _frameExtent.y()};
	Point const bottomRight{topRight.x(), bottomLeft.y()};

	Brush const verticalBrush{'|'};
	_inner->setBrush(verticalBrush);
	Line const leftLine{topLeft, bottomLeft};
	_inner->paint(leftLine);
	Line const rightLine{topRight, bottomRight};
	_inner->paint(rightLine);

	// Paints over the vertical lines in top row
	Brush const horizontalBrush{'_'};
	_inner->setBrush(horizontalBrush);
	Line const horizontalLine{topLeft, topRight};
	_inner->paint(horizontalLine);

}

void Painter::paintBoard() {
	using luanics::graphics::Offset;
	using luanics::graphics::Point;

	Offset const textOffset{0, -1};
	Offset const frameToFrameOffset{_frameExtent.x() + HORIZONTAL_SPACE.x() + 1, 0};

	Point topLeft = _foundationsStart;
	for (unsigned i = 0; i < Model::NUM_FOUNDATIONS; ++i) {
		paintFrame(topLeft);
		auto const label = std::to_string(i + 1);
		_inner->paint(std::to_string(i+1), topLeft + textOffset);
		topLeft += frameToFrameOffset;
	}

	topLeft = _cellsStart;
	for (unsigned i = 0; i < Model::NUM_CELLS; ++i) {
		paintFrame(topLeft);
		auto const label = std::to_string(i + 1 + Model::NUM_FOUNDATIONS);
		_inner->paint(label, topLeft + textOffset);
		topLeft += frameToFrameOffset;
	}

	topLeft = _cascadesStart;
	for (unsigned i = 0; i < Model::NUM_CASCADES; ++i) {
		paintFrame(topLeft);
		auto const label = std::string(1, 'a' + i);
		_inner->paint(label, topLeft + textOffset);
		topLeft += frameToFrameOffset;
	}
}

void Painter::paint(Model const & model) {
	using luanics::graphics::Offset;
	using luanics::graphics::Point;

	Offset const cardToCardOffset{_frameExtent.x() + HORIZONTAL_SPACE.x() + 1, 0};
	Offset const frameToCardOffset{1,1};

	// Foundations
	Point topLeft = _foundationsStart + frameToCardOffset;
	for (unsigned i = 0; i < Model::NUM_FOUNDATIONS; ++i) {
		paint(model.foundations()[i], topLeft);
		topLeft += cardToCardOffset;
	}

	// Cells
	topLeft = _cellsStart + frameToCardOffset;
	for (unsigned i = 0; i < Model::NUM_CELLS; ++i) {
		paint(model.cells()[i], topLeft);
		topLeft += cardToCardOffset;
	}

	// Text
	_inner->paint(model.text(), _textStart);

	topLeft = _cascadesStart + frameToCardOffset;
	for (unsigned i = 0; i < Model::NUM_CASCADES; ++i) {
		paint(model.cascades()[i], topLeft);
		topLeft += cardToCardOffset;
	}
}

void Painter::paint(
	Cascade const & cascade,
	luanics::graphics::Point const & topLeft
) {
	if (cascade.isEmpty()) {
		paintCardBack(_spec, topLeft, *_inner);
	}
	else {
		auto current = topLeft;
		luanics::graphics::Offset const cardToCardOffset{0, 2};
		for (auto const & card: cascade.cards()) {
			luanics::cards::paintCardFront(card, _spec, current, *_inner);
			current += cardToCardOffset;
		}
	}
}

void Painter::paint(
	Cell const & cell,
	luanics::graphics::Point const & topLeft
) {
	if (cell.isEmpty()) {
		paintCardBack(_spec, topLeft, *_inner);
	}
	else {
		luanics::cards::paintCardFront(cell.cards().back(), _spec, topLeft, *_inner);
	}
}

void Painter::paint(
	Foundation const & foundation,
	luanics::graphics::Point const & topLeft
) {
	if (foundation.isEmpty()) {
		paintCardBack(_spec, topLeft, *_inner);
	}
	else {
		luanics::cards::paintCardFront(foundation.cards().back(), _spec, topLeft, *_inner);
	}
}

}  // namespace freecell
}  // namespace cards
}  // namespace luanics
