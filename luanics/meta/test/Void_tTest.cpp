#include "luanics/meta/Void_t.hpp"
#include "luanics/test/Unit.hpp"

#include <type_traits>

using namespace luanics;

BEGIN_TEST_SET(Void_t)

TEST(All) {
	bool const areSame = std::is_same<void, Void_t<int, bool>>::value;
	EXPECT_TRUE(areSame)
}

END_TEST_SET(Void_t)
