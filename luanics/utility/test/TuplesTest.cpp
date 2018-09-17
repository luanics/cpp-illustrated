#include "luanics/utility/Tuples.hpp"
#include "luanics/testing/Unit.hpp"


//*******************************************************************
// Library
//*******************************************************************


using namespace luanics::tuples;

BEGIN_TEST_SET(Tuples)

TEST(Writer) {
	std::tuple<char, int> values('A', 1);
	std::ostringstream out;
	write(values, out);
	EXPECT_EQ("A 1 ", out.str());
}

END_TEST_SET(Tuples)
