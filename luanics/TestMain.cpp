#include "luanics/testing/Unit.hpp"
#include "luanics/testing/core/ReporterAugmenter.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"

#include <iostream>

int main() {
	bool const isUsingColor = true;
	bool const isTerse = false;

	luanics::testing::unit::StandardReporter reporter{&std::cout, isUsingColor, isTerse};
	luanics::testing::core::ReporterAugmenter augmenter{&reporter};
	luanics::testing::unit::suiteInstance().run(augmenter);

	return 0;
}
