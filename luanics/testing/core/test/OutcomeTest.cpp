#include "luanics/testing/Unit.hpp"
#include "luanics/testing/core/Outcome.hpp"

namespace luanics::testing::core {

BEGIN_TEST_SET(Outcome)

TEST(Combine) {
	EXPECT_EQ(Outcome::NONE, combined(Outcome::NONE, Outcome::NONE));
	EXPECT_EQ(Outcome::PASS, combined(Outcome::PASS, Outcome::NONE));
	EXPECT_EQ(Outcome::PASS, combined(Outcome::NONE, Outcome::PASS));
	EXPECT_EQ(Outcome::PASS, combined(Outcome::PASS, Outcome::PASS));
	EXPECT_EQ(Outcome::FAIL, combined(Outcome::FAIL, Outcome::NONE));
	EXPECT_EQ(Outcome::FAIL, combined(Outcome::FAIL, Outcome::PASS));
	EXPECT_EQ(Outcome::FAIL, combined(Outcome::FAIL, Outcome::FAIL));
	EXPECT_EQ(Outcome::ERROR, combined(Outcome::ERROR, Outcome::NONE));
	EXPECT_EQ(Outcome::ERROR, combined(Outcome::ERROR, Outcome::PASS));
	EXPECT_EQ(Outcome::ERROR, combined(Outcome::ERROR, Outcome::FAIL));
	EXPECT_EQ(Outcome::ERROR, combined(Outcome::ERROR, Outcome::ERROR));
}

END_TEST_SET(Outcome)

} // namespace luanics::testing::core
