#include "luanics/string/AllMatcher.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::string {

BEGIN_TEST_SET(AllMatcher)

TEST(All) {
	AllMatcher matcher;
	EXPECT_TRUE(matcher(""));
	EXPECT_TRUE(matcher("something"));
}

END_TEST_SET(AllMatcher)

} // namespace luanics::string
