#include "luanics/grid/SubGrid.hpp"
#include "luanics/grid/DynamicGrid.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Streams.hpp"

#include <iostream>
#include <sstream>

namespace luanics::grid {

BEGIN_TEST_SET(SubGrid)

TEST(Basics) {
	DynamicGrid basic{5, 5};
	SubGrid sub{3, 3, 1, 1, &basic};
	EXPECT_EQ(3, sub.width());
	EXPECT_EQ(3, sub.height());
	EXPECT_EQ(1, sub.xOffset());
	EXPECT_EQ(1, sub.yOffset());

	EXPECT_EQ(Grid::EmptyValue, basic(1,1));
	EXPECT_EQ(Grid::EmptyValue, sub(0,0));
	EXPECT_EQ(Grid::EmptyValue, basic(3,3));
	EXPECT_EQ(Grid::EmptyValue, sub(2,2));
	EXPECT_EQ(Grid::EmptyValue, basic(3,2));
	EXPECT_EQ(Grid::EmptyValue, sub(2,1));

	char const star = '*';
	char const dot = '.';
	char const hash = '#';
	sub(0,0) = star;
	sub(2,2) = dot;
	sub(1,2) = hash;
	EXPECT_EQ(star, basic(1,1));
	EXPECT_EQ(star, sub(0,0));
	EXPECT_EQ(dot, basic(3,3));
	EXPECT_EQ(dot, sub(2,2));
	EXPECT_EQ(hash, basic(2,3));
	EXPECT_EQ(hash, sub(1,2));
}

TEST(Fill) {
	DynamicGrid basic{5, 5};
	SubGrid sub{3, 3, 1, 1, &basic};
	char const dot = '.';
	sub.fillWith(dot);
	EXPECT_EQ(dot, basic(1,1));
	EXPECT_EQ(dot, sub(0,0));
	EXPECT_EQ(dot, basic(3,3));
	EXPECT_EQ(dot, sub(2,2));
}

TEST(Write) {
	DynamicGrid basic{5, 5};
	SubGrid sub{3, 3, 1, 1, &basic};
	char const dot = '.';
	basic.fillWith(dot);

	std::ostringstream out;
	out << sub;
	std::string expected =
		"...\n"
		"...\n"
		"...\n"
	;
	EXPECT_EQ(expected, out.str());

	utility::streams::reset(out);
	char const star = '*';
	basic(1,1) = star;
	basic(3,2) = star;
	expected =
		"...\n"
		"..*\n"
		"*..\n"
	;
	out << sub;
	EXPECT_EQ(expected, out.str());
}

TEST(Read) {
	DynamicGrid basic{5, 5};
	SubGrid sub{3, 3, 1, 1, &basic};
	char const dot = '.';
	basic.fillWith(dot);
	std::string const data =
		"123\n"
		"456\n"
		"789\n"
	;
	std::istringstream in(data);
	in >> sub;

	std::ostringstream out;
	out << basic;
	std::string const expected =
		".....\n"
		".123.\n"
		".456.\n"
		".789.\n"
		".....\n"
	;
	EXPECT_EQ(expected, out.str());
}

END_TEST_SET(SubGrid)

} // namespace luanics::grid
