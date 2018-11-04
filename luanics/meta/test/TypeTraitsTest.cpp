#include "luanics/meta/TypeTraits.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <type_traits>

using namespace luanics;

BEGIN_TEST_SET(TypeTraits)

class Empty {};

TEST(All) {
	bool const isIntStreamInsertable = IsStreamInsertable_v<int>;
	EXPECT_TRUE(isIntStreamInsertable);

	bool const isEmptyStreamInsertable = IsStreamInsertable_v<Empty>;
	EXPECT_FALSE(isEmptyStreamInsertable);
}

END_TEST_SET(TypeTraits)
