#include "luanics/string/Manipulation.hpp"
#include "luanics/testing/Unit.hpp"

using namespace luanics::string;
using namespace std;

BEGIN_TEST_SET(Manipulation)

TEST(Split) {
	string const namesString("able baker charlie");
	string const whitespace(" \n\t");
	auto names = split(namesString, whitespace);
	EXPECT_EQ(3U, names.size());
	EXPECT_EQ("able", names[0]);
	EXPECT_EQ("baker", names[1]);
	EXPECT_EQ("charlie", names[2]);

	string const pathString("Names.First");
	string const pathDelimiter(".");
	auto paths = split(pathString, pathDelimiter);
	EXPECT_EQ(2U, paths.size());
}

TEST(Join) {
	vector<int> numbers{1, 2, 3};
	ostringstream out;
	join(numbers, out, ",");
	EXPECT_EQ("1,2,3", out.str());
}

END_TEST_SET(Manipulation)
