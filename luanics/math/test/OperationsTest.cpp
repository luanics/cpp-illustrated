#include "luanics/math/Operations.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics {
namespace math {

BEGIN_TEST_SET(Operations)

TEST(Modulo) {
	EXPECT_EQ(2, modulo(5,3));
	EXPECT_EQ(1, modulo(4,3));
	EXPECT_EQ(0, modulo(3,3));
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

} // namespace math
} // namespace luanics
