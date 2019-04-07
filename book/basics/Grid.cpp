#include "luanics/grid/DynamicGrid.hpp"
#include "luanics/grid/SubGrid.hpp"
#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <sstream>

using namespace luanics;

//*********************************************************
// DynamicGrid
//*********************************************************


int main() {
	utility::Herald herald{"Grid"};

	//*********************************************************
	// DynamicGrid
	//*********************************************************

	grid::DynamicGrid grid;
	std::istringstream in{
R"( ,-,
/-(
\ {
 `-`)"};
	in >> grid;

	std::cout << "sleeping moon" << '\n';
	std::cout << grid;

	constexpr char closedEye = '-';
	assert(grid(1,2) == closedEye);
	constexpr char openEye = '.';
	grid(1,2) = openEye;

	std::cout << "awake moon" << '\n';
	std::cout << grid;

	//*********************************************************
	// SubGrid
	//*********************************************************

	constexpr unsigned width = 1;
	constexpr unsigned height = 2;
	constexpr unsigned xOffset = 1;
	constexpr unsigned yOffset = 1;
	grid::SubGrid subGrid{width, height, xOffset, yOffset, &grid};

	subGrid.fillWith('0');
	std::cout << "monster moon" << '\n';
	std::cout << grid;

	return 0;
}
