#include "luanics/cards/Rank.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

namespace luanics::cards {

BEGIN_TEST_SET(Rank)

TEST(IsFace) {
	EXPECT_FALSE(isFace(Rank::TWO));
	EXPECT_TRUE(isFace(Rank::JACK));
	EXPECT_FALSE(isFace(Rank::ACE));
}

TEST(IsLess) {
	// Aces low
	EXPECT_FALSE(isLess(Rank::TWO, Rank::TWO, false));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::THREE, false));
	EXPECT_FALSE(isLess(Rank::THREE, Rank::TWO, false));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::JACK, false));
	EXPECT_FALSE(isLess(Rank::JACK, Rank::TWO, false));
	EXPECT_FALSE(isLess(Rank::TWO, Rank::ACE, false));
	EXPECT_TRUE(isLess(Rank::ACE, Rank::TWO, false));
	EXPECT_FALSE(isLess(Rank::JACK, Rank::ACE, false));
	EXPECT_TRUE(isLess(Rank::ACE, Rank::JACK, false));

	// Aces high
	EXPECT_FALSE(isLess(Rank::TWO, Rank::TWO, true));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::THREE, true));
	EXPECT_FALSE(isLess(Rank::THREE, Rank::TWO, true));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::JACK, true));
	EXPECT_FALSE(isLess(Rank::JACK, Rank::TWO, true));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::ACE, true));
	EXPECT_FALSE(isLess(Rank::ACE, Rank::TWO, true));
	EXPECT_TRUE(isLess(Rank::JACK, Rank::ACE, true));
	EXPECT_FALSE(isLess(Rank::ACE, Rank::JACK, true));
}

TEST(Io) {
	std::ostringstream out;
	out << Rank::TWO;
	EXPECT_EQ("TWO", out.str());

	utility::reset(out);
	out << Rank::JACK;
	EXPECT_EQ("JACK", out.str());

	std::istringstream in;
	Rank rank;

	utility::reset(in, "TWO");
	in >> rank;
	EXPECT_EQ(Rank::TWO, rank);

	utility::reset(in, "JACK");
	in >> rank;
	EXPECT_EQ(Rank::JACK, rank);

	utility::reset(in, "JILL");
	EXPECT_THROW(in >> rank);

	PRINT("Hello");
}

END_TEST_SET(Rank)

} // namespace luanics::cards
