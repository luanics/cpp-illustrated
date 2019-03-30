#include "luanics/memory/Checking.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/testing/core/ReporterAugmenter.hpp"
#include "luanics/testing/core/StringExcluderDecorator.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"

#include <iostream>

int main() {
	bool const isUsingColor = true;
	bool const isTerse = false;

	luanics::testing::unit::StandardReporter reporter{&std::cout, isUsingColor, isTerse};
	luanics::testing::core::StringExcluderDecorator filter{&reporter, "_Tutorial"};
	luanics::testing::core::ReporterAugmenter augmenter{&filter};
	luanics::testing::unit::suiteInstance().run(augmenter);

	auto result = reporter.numTestsFailed() == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	return result;
}
