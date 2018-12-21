#pragma once

#include "luanics/graphics/Painter.hpp"
#include "luanics/graphics/Offset.hpp"
#include "luanics/graphics/Point.hpp"

/// Idea - Resizeable layout system.

namespace luanics { namespace graphics { class Painter; }}

namespace luanics {
namespace cards {
namespace freecell {

class Cascade;
class Cell;
class Foundation;
class Model;

class Painter {
public:
	Painter(
		luanics::graphics::Painter * inner,
		CardPaintSpec const & spec = CardPaintSpec{}
	);

	void paint(Model const & model);
	void paintBoard();

private:
	void paint(
		Cascade const & cascade,
		luanics::graphics::Point const & topLeft
	);
	void paint(
		Cell const & cell,
		luanics::graphics::Point const & topLeft
	);
	void paint(
		Foundation const & foundation,
		luanics::graphics::Point const & topLeft
	);
	void paintFrame(luanics::graphics::Point const & topLeft);

	luanics::graphics::Painter * _inner;
	CardPaintSpec _spec;
	luanics::graphics::Offset _frameExtent;
	luanics::graphics::Point _foundationsStart;
	luanics::graphics::Point _cellsStart;
	luanics::graphics::Point _cascadesStart;
	luanics::graphics::Point _textStart;
}; // class Painter

}  // namespace freecell
}  // namespace cards
}  // namespace luanics
