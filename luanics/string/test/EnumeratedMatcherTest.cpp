#include "luanics/string/EnumeratedMatcher.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::string {

BEGIN_TEST_SET(EnumeratedMatcher)

TEST(Empty) {
	EnumeratedMatcher matcher{{}};
	EXPECT_FALSE(matcher(""));
	EXPECT_FALSE(matcher("something"));
}

TEST(NotEmpty) {
	EnumeratedMatcher matcher{{"", "cat","dog"}};
	EXPECT_TRUE(matcher(""));
	EXPECT_FALSE(matcher("bird"));
	EXPECT_TRUE(matcher("cat"));
	EXPECT_TRUE(matcher("dog"));
	EXPECT_FALSE(matcher("doggy"));
}

END_TEST_SET(EnumeratedMatcher)

} // namespace luanics::string
