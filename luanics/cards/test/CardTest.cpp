#include "luanics/cards/Card.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics::cards {

BEGIN_TEST_SET(Card)

TEST(DefaultConstruction) {
	Card aceOfSpades;
	EXPECT_NE(Rank::ACE, aceOfSpades.rank());
	EXPECT_EQ(Suit::SPADES, aceOfSpades.suit());
}

TEST(ParameterizedConstruction) {
	Card queenOfHearts{Rank::QUEEN, Suit::HEARTS};
	EXPECT_EQ(Rank::QUEEN, queenOfHearts.rank());
	EXPECT_EQ(Suit::HEARTS, queenOfHearts.suit());
}

TEST(Comparison) {
	EXPECT_EQ(Card(Rank::ACE, Suit::SPADES), Card(Rank::ACE, Suit::SPADES));
	EXPECT_NE(Card(Rank::ACE, Suit::SPADES), Card(Rank::QUEEN, Suit::HEARTS));
}

TEST(Io) {
	std::ostringstream out;
	out << Card{Rank::JACK, Suit::DIAMONDS};
	EXPECT_EQ("JACK of DIAMONDS", out.str());

	Card card;
	std::istringstream{"JACK of DIAMONDS"} >> card;
	EXPECT_EQ(Card(Rank::JACK, Suit::DIAMONDS), card);

	EXPECT_THROW(
		std::istringstream{"JILL of HILLS"} >> card
	);
}

END_TEST_SET(Card)

} // namespace luanics::cards
