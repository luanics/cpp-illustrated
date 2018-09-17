#include "luanics/string/AllMatcher.hpp"
#include "luanics/string/ExactMatcher.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/testing/unit/StandardReporter.hpp"
#include "luanics/testing/unit/Filter.hpp"
#include "luanics/testing/unit/ReporterAdapter.hpp"

using namespace luanics::string;
using namespace luanics::testing::unit;
using namespace std;

#include <iostream>

int main() {
	bool const isUsingColor = true;
	bool const isTerse = false;
	StandardReporter reporter{&cout, isUsingColor, isTerse};
	Filter filter{
		std::unique_ptr<AllMatcher>(new AllMatcher{}),
		std::unique_ptr<AllMatcher>(new AllMatcher{}),
		&reporter
	};
	ReporterAdapter adapter{&filter};

	suiteInstance.run(adapter);

	return 0;
}
