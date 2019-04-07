#include "luanics/grid/DynamicGrid.hpp"
#include "luanics/grid/SubGrid.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <sstream>

using namespace luanics::grid;
using namespace std;

BEGIN_CHAPTER(Grid)

SECTION(DynamicGrid) {

	// Create a DynamicGrid that matches this output...
	std::string expectedBoxOutput{
		"****" "\n"
		"****" "\n"
	};
	// This can be done in two lines of code
	FIX(DynamicGrid box;)
	std::ostringstream actualBoxOutput;
	actualBoxOutput << box;
	EXPECT_EQ(expectedBoxOutput, actualBoxOutput.str());

	// Create a DynamicGrid that matches this output...
	std::string expectedSmileOutput{
		"*  *" "\n"
		"****" "\n"
	};
}

SECTION(SubGrid) {
	// Match the following output using a DynamicGrid and SubGrid...
	std::string expectedWindowOutput{
		"*****" "\n"
		"*...*" "\n"
		"*...*" "\n"
		"*...*" "\n"
		"*****" "\n"
	};

}

END_CHAPTER(Grid)
