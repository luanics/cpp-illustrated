#include "luanics/cards/Card.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics::cards {

BEGIN_TEST_SET(Card)              // test set: "Card"

TEST(Comparison) {                // test: "Comparison"
	ASSERT_EQ(                     // test statement
		Card(Rank::ACE, Suit::HEARTS),
		Card(Rank::ACE, Suit::SPADES)
	);
	ASSERT_NE(                     // test statement
		Card(Rank::ACE, Suit::SPADES),
		Card(Rank::ACE, Suit::SPADES)
	)
}

TEST(Io) {                        // test: "Io"
	std::ostringstream out;
	out << Card{Rank::JACK, Suit::DIAMONDS};
	EXPECT_EQ(                     // test statement
		"JACK of DIAMONDS",
		out.str()
	);

	Card card;
	std::istringstream{"JACK of DIAMONDS"} >> card;
	EXPECT_EQ(                     // test statement
		Card(Rank::JACK, Suit::DIAMONDS),
		card
	);

	EXPECT_THROW(                  // test statement
		std::istringstream{"JILL of HILLS"} >> card
	);
}

END_TEST_SET(Card)

} // namespace luanics::cards
