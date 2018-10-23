#include "luanics/crypto/Helpers.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::crypto {

BEGIN_TEST_SET(Helpers)

TEST(DistanceFromA) {
	EXPECT_EQ(0, distanceFromA('a'));
	EXPECT_EQ(25, distanceFromA('z'));
	EXPECT_THROW(distanceFromA('1'));
	EXPECT_THROW(distanceFromA('%'));
	EXPECT_THROW(distanceFromA('A'));
}

TEST(Shift) {
	EXPECT_EQ('c', shift('a', 2));
	EXPECT_EQ('a', shift('y', 2));

	EXPECT_EQ('y', shift('a', -2));
	EXPECT_EQ('a', shift('c', -2));
}

END_TEST_SET(Helpers)

} // namespace luanics::crypto
