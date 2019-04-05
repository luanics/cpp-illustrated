#include "luanics/grid/DynamicGrid.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <sstream>

namespace luanics::grid {

BEGIN_TEST_SET(DynamicGrid)

TEST(Basics) {
	DynamicGrid buffer(5, 5);
	EXPECT_EQ(5, buffer.width());
	EXPECT_EQ(5, buffer.height());

	char const star = '*';
	char const dot = '.';
	buffer(1,1) = star;
	buffer(2,2) = dot;
	EXPECT_EQ(star, buffer(1,1));
}

TEST(Fill) {
	DynamicGrid buffer(5,5);
	char const dot = '.';
	buffer.fillWith(dot);
	EXPECT_EQ(dot, buffer(1,1));
	EXPECT_EQ(dot, buffer(4,4));
}

TEST(Write) {
	DynamicGrid buffer(5, 3);
	char const dot = '.';
	buffer.fillWith(dot);
	char const star = '*';
	buffer(3, 2) = star;
	std::string const expected =
		"...*.\n"
		".....\n"
		".....\n";
	std::ostringstream out;
	buffer.writeTo(out);
	EXPECT_EQ(expected, out.str());
	// Having problems here? Make sure you have operator() defined correctly!
}

TEST(Read) {
	std::string const data =
		".*...\n"
		".....\n"
		".....\n";
	std::istringstream in(data);
	DynamicGrid buffer(5, 3);
	buffer.readFrom(in);
	char const star = '*';
	char const dot = '.';
	EXPECT_EQ(5, buffer.width());
	EXPECT_EQ(3, buffer.height());
	EXPECT_EQ(star, buffer(1,2));
	EXPECT_EQ(dot, buffer(0,0));
}

END_TEST_SET(DynamicGrid)

} // namespace luanics::grid
