#include "luanics/grid/DynamicGrid.hpp"
#include "luanics/grid/FlippedGrid.hpp"
#include "luanics/testing/Unit.hpp"

#include <sstream>

namespace luanics::grid {

BEGIN_TEST_SET(FlippedGrid_Tutorial)

TEST(All) {
	auto decorated = std::make_unique<DynamicGrid>(4, 3);
	FlippedGrid grid{std::move(decorated)};
	EXPECT_EQ(4, grid.width());
	EXPECT_EQ(3, grid.height());
	EXPECT_THROW(grid(4,3));

	std::istringstream in{
		"*..." "\n"
		"...." "\n"
		"...." "\n"
	};
	in >> grid;
	EXPECT_EQ('*', grid(0,0));
	EXPECT_EQ('.', grid(3,2));

	grid(3,2) = '@';
	std::ostringstream out;
	out << grid;
	std::string const expectedOut{
		"*..." "\n"
		"...." "\n"
		"...@" "\n"
	};
	EXPECT_EQ(expectedOut, out.str());
}

END_TEST_SET(FlippedGrid)

} // namespace luanics::grid
