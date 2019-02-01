#include "luanics/cards/Rank.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics::cards {

BEGIN_TEST_SET(Rank)                // test set: "Rank"

TEST(IsFace) {                      // test: "IsFace"
	EXPECT_TRUE(isFace(Rank::TWO)); // test statement
	EXPECT_TRUE(isFace(Rank::JACK)); // test statement
	EXPECT_FALSE(isFace(Rank::ACE)); // test statement
}

TEST(Io) {                          // test: "Io"
	std::ostringstream out;
	out << Rank::JACK;
	EXPECT_EQ("JACK", out.str());    // test statement

	Rank rank;
	std::istringstream{"JACK"} >> rank;
	EXPECT_EQ(Rank::JACK, rank);     // test statement

	EXPECT_THROW(                    // test statement
		std::istringstream{"JILL"} >> rank
	);
}

END_TEST_SET(Rank)

} // namespace luanics::cards
