#include "luanics/string/ExactMatcher.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::string {

BEGIN_TEST_SET(ExactMatcher)

TEST(All) {
	ExactMatcher matcher("target");
	EXPECT_FALSE(matcher(""));
	EXPECT_FALSE(matcher("source"));
	EXPECT_TRUE(matcher("target"));
}

END_TEST_SET(ExactMatcher)

} // namespace luanics::string
