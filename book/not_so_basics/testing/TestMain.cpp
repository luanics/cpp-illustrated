#include "luanics/testing/Unit.hpp"
#include "luanics/testing/core/ReporterAugmenter.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"

#include <iostream>

using namespace luanics::testing;

int main() {
	bool const isUsingColor = false;
	bool const isTerse = false;

	unit::StandardReporter reporter{&std::cout, isUsingColor, isTerse};
	core::ReporterAugmenter augmenter{&reporter};
	unit::suiteInstance().run(augmenter);

	return 0;
}
