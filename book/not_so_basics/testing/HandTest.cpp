#include "Hand.hpp"

#include <luanics/testing/Unit.hpp>

namespace luanics::cards::blackjack {

BEGIN_TEST_SET(Hand)                  // test set: "Hand"

TEST(Add) {                           // test: "Add"
	Hand hand;
	EXPECT_EQ(0, hand.cards().size()); // test statement

	Card const aceOfSpades{Rank::ACE, Suit::SPADES};
	hand.add(aceOfSpades);
	ASSERT_EQ(1, hand.cards().size()); // test statement
	EXPECT_EQ(                         // test statement
		aceOfSpades,
		hand.cards().back()
	);
}

TEST(ScoreWithoutAces) {              // test: "ScoreWithoutAces"
	Hand hand;
	EXPECT_EQ(0, hand.score());

	hand.add(Card{Rank::EIGHT, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(8, hand.score());        // test statement

	hand.add(Card{Rank::KING, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(18, hand.score());       // test statement

	hand.add(Card{Rank::THREE, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(21, hand.score());       // test statement

	hand.add(Card{Rank::TWO, Suit::HEARTS});
	EXPECT_TRUE(hand.isBust());        // test statement
	EXPECT_EQ(-1, hand.score());       // test statement
}

TEST(ScoreWithAces) {                 // test: "ScoreWithAces"
	Hand hand;
	EXPECT_EQ(0, hand.score());

	hand.add(Card{Rank::ACE, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(11, hand.score());       // test statement

	hand.add(Card{Rank::KING, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(21, hand.score());       // test statement

	hand.add(Card{Rank::JACK, Suit::HEARTS});
	EXPECT_FALSE(hand.isBust());       // test statement
	EXPECT_EQ(21, hand.score());       // test statement

	hand.add(Card{Rank::TWO, Suit::HEARTS});
	EXPECT_TRUE(hand.isBust());        // test statement
	EXPECT_EQ(-1, hand.score());       // test statement
}

END_TEST_SET(Hand)

} // namespace luanics::cards::blackjack
