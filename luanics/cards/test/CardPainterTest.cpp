#include "luanics/cards/CardPainter.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics {
namespace cards {

using namespace graphics;

BEGIN_TEST_SET(CardPainter)

TEST(FaceUp) {
	DynamicGrid grid{7, 6};
	Painter painter{&grid};
	Brush const faceUpBrush{'*', ' '};
	Brush const faceDownBrush{'*', '@'};
	Offset const topRight{7, 6};
	Offset const nameOffset{1, 1};
	Offset const colorOffset{5, 1};
	CardPainter const cardPainter{
		faceUpBrush,
		faceDownBrush,
		topRight,
		nameOffset,
		colorOffset
	};

	EXPECT_EQ(6, cardPainter.height());
	EXPECT_EQ(7, cardPainter.width());

	std::ostringstream out;
	cardPainter.paintFaceDown(
		Point{0,0},
		Card{Rank::NINE, Suit::DIAMONDS},
		painter
	);
	grid.writeTo(out);

	std::string const expectedFaceDown =
		"*******" "\n"
		"*@@@@@*" "\n"
		"*@@@@@*" "\n"
		"*@@@@@*" "\n"
		"*@@@@@*" "\n"
		"*******" "\n"
	;
	EXPECT_EQ(expectedFaceDown, out.str());
	reset(out);
	grid.clear();

	cardPainter.paintFaceUp(
		Point{0,0},
		Card{Rank::NINE, Suit::DIAMONDS},
		painter
	);
	grid.writeTo(out);
	std::string const expectedFaceUp =
			"*******" "\n"
			"*9D  r*" "\n"
			"*     *" "\n"
			"*     *" "\n"
			"*     *" "\n"
			"*******" "\n";
	EXPECT_EQ(expectedFaceUp, out.str());
}

END_TEST_SET(CardPainter)

} // namespace cards
} // namespace luanics
