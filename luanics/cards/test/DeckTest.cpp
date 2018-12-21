#include "luanics/cards/Deck.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics {
namespace cards {

BEGIN_TEST_SET(Deck)

TEST(All) {
	Deck deck{};
	PRINT(deck.size());
	EXPECT_EQ(52, deck.size());

	// Unshuffled deck goes from high to low, starting with ACE of SPADES.
	// Check first two cards.
	Card card = deck.draw();
	EXPECT_EQ((Card{Rank::ACE, Suit::SPADES}), card);
	ASSERT_EQ(51, deck.size());
	card = deck.draw();
	EXPECT_EQ((Card{Rank::ACE, Suit::HEARTS}), card);
	EXPECT_EQ(50, deck.size());

	// Check that last card is TWO of CLUBS
	while (not deck.isEmpty()) {
		card = deck.draw();
	}
	EXPECT_EQ((Card{Rank::TWO, Suit::CLUBS}), card);
}

END_TEST_SET(Deck)

} // namespace cards
} // namespace luanics

