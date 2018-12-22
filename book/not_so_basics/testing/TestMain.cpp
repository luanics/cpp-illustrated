#include "luanics/testing/Unit.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"
#include "luanics/testing/unit/ReporterAdapter.hpp"

using namespace luanics::testing::unit;

#include <iostream>

int main() {
	bool const isUsingColor = true;
	bool const isTerse = false;
	StandardReporter reporter{&std::cout, isUsingColor, isTerse};
	ReporterAdapter adapter{&reporter};
	suiteInstance.run(adapter);
	return 0;
}
