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

TEST(DistanceWithAceHigh) {
	// Ace high
	bool const isAceHigh = true;
	EXPECT_EQ(0, distance(Rank::TWO, Rank::TWO, isAceHigh));
	EXPECT_EQ(1, distance(Rank::TWO, Rank::THREE, isAceHigh));
	EXPECT_EQ(-1, distance(Rank::THREE, Rank::TWO, isAceHigh));
	EXPECT_EQ(9, distance(Rank::TWO, Rank::JACK, isAceHigh));
	EXPECT_EQ(-9, distance(Rank::JACK, Rank::TWO, isAceHigh));
	EXPECT_EQ(12, distance(Rank::TWO, Rank::ACE, isAceHigh));
	EXPECT_EQ(-12, distance(Rank::ACE, Rank::TWO, isAceHigh));
	EXPECT_EQ(3, distance(Rank::JACK, Rank::ACE, isAceHigh));
	EXPECT_EQ(-3, distance(Rank::ACE, Rank::JACK, isAceHigh));
}

TEST(DistanceWithAceLow) {
	// Ace low
	bool const isAceHigh = false;
	EXPECT_EQ(-1, distance(Rank::TWO, Rank::ACE, isAceHigh));
	EXPECT_EQ(1, distance(Rank::ACE, Rank::TWO, isAceHigh));
	EXPECT_EQ(-10, distance(Rank::JACK, Rank::ACE, isAceHigh));
	EXPECT_EQ(10, distance(Rank::ACE, Rank::JACK, isAceHigh));
}

TEST(IsLessWithAceHigh) {
	// Ace high
	bool const isAceHigh = true;
	EXPECT_FALSE(isLess(Rank::TWO, Rank::TWO, isAceHigh));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::THREE, isAceHigh));
	EXPECT_FALSE(isLess(Rank::THREE, Rank::TWO, isAceHigh));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::JACK, isAceHigh));
	EXPECT_FALSE(isLess(Rank::JACK, Rank::TWO, isAceHigh));
	EXPECT_TRUE(isLess(Rank::TWO, Rank::ACE, isAceHigh));
	EXPECT_FALSE(isLess(Rank::ACE, Rank::TWO, isAceHigh));
	EXPECT_TRUE(isLess(Rank::JACK, Rank::ACE, isAceHigh));
	EXPECT_FALSE(isLess(Rank::ACE, Rank::JACK, isAceHigh));
}

TEST(IsLessWithAceLow) {
	// Ace low
	bool const isAceHigh = false;
	EXPECT_FALSE(isLess(Rank::TWO, Rank::ACE, isAceHigh));
	EXPECT_TRUE(isLess(Rank::ACE, Rank::TWO, isAceHigh));
	EXPECT_FALSE(isLess(Rank::JACK, Rank::ACE, isAceHigh));
	EXPECT_TRUE(isLess(Rank::ACE, Rank::JACK, isAceHigh));
}

TEST(Io) {
	std::ostringstream out;
	out << Rank::JACK;
	EXPECT_EQ("JACK", out.str());

	Rank rank;
	std::istringstream{"JACK"} >> rank;
	EXPECT_EQ(Rank::JACK, rank);

	EXPECT_THROW(std::istringstream{"JILL"} >> rank);
}

END_TEST_SET(Rank)

} // namespace luanics::cards
