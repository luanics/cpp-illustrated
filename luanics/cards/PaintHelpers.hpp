#pragma once

namespace luanics {
	class FlippedGrid;
	namespace graphics { class Offset; class Point; }
namespace cards {

void paintFrame(
	graphics::Offset const & cardSize,
	graphics::Point const & topLeft,
	FlippedGrid & grid
};

} // namespace cards
} // namespace luanics
