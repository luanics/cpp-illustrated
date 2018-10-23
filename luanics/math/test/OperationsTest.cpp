#include "luanics/math/Operations.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::math {

BEGIN_TEST_SET(Operations)

TEST(Modulo) {
	EXPECT_EQ(2, positiveModulo(5,3));
	EXPECT_EQ(1, positiveModulo(4,3));
	EXPECT_EQ(0, positiveModulo(3,3));
}

TEST(Sign) {
	EXPECT_EQ(-1, sign(-100.0));
	EXPECT_EQ(-1, sign(-100));
	EXPECT_EQ(0, sign(0.0));
	EXPECT_EQ(0.0, sign(0));
	EXPECT_EQ(1, sign(100.0));
	EXPECT_EQ(1, sign(100));
}

END_TEST_SET(Operations)

} // namespace luanics::math
