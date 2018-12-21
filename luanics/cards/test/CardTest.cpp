#include "luanics/cards/Card.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::cards {

BEGIN_TEST_SET(Card)

TEST(DefaultConstruction) {
	Card aceOfSpades;
	EXPECT_EQ(Rank::ACE, aceOfSpades.rank());
	EXPECT_EQ(Suit::SPADES, aceOfSpades.suit());
}

TEST(ParameterizedConstruction) {
	Card queenOfHearts{Rank::QUEEN, Suit::HEARTS};
	EXPECT_EQ(Rank::QUEEN, queenOfHearts.rank());
	EXPECT_EQ(Suit::HEARTS, queenOfHearts.suit());
}

TEST(Comparison) {                     // test: "Comparison"
	EXPECT_EQ(Card(Rank::ACE, Suit::SPADES), Card(Rank::ACE, Suit::SPADES));
	EXPECT_NE(Card(Rank::ACE, Suit::SPADES), Card(Rank::QUEEN, Suit::HEARTS))
}

TEST(Io) {

}

END_TEST_SET(Card)

} // namespace luanics::cards
