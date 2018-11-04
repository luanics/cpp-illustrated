#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Herald.hpp"

namespace luanics::utility {

BEGIN_TEST_SET(Herald)

std::string expectedOutput{
R"(starting Test ...
... finished Test
)"
};

TEST(All) {
	std::ostringstream out;
	{
		Herald test{"Test", &out};
	}
	EXPECT_EQ(expectedOutput, out.str());
}

END_TEST_SET(Herald)

} // namespace luanics::utility
