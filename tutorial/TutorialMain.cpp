#include "luanics/testing/Tutorial.hpp"
#include "luanics/testing/tutorial/FirstFailFilter.hpp"
#include "luanics/testing/tutorial/ReporterAdapter.hpp"
#include "luanics/testing/tutorial/StandardReporter.hpp"

#include <cstring>
#include <iostream>

using namespace luanics::testing::core;
using namespace luanics;
using namespace std;

constexpr const char * noColorOptionName = "--no-color";
constexpr const char * hintsOptionName = "--hints";
constexpr const char * runAllOptionName = "--run-all";
constexpr const char * helpOptionName = "--help";
std::vector<const char *> optionNames{
	noColorOptionName,
	hintsOptionName,
	runAllOptionName,
	helpOptionName
};

ADD_TUTORIAL(Tutorial)

ADD_PART(Basics, true)
ADD_CHAPTER(Basics, GettingStarted, true)
ADD_CHAPTER(Basics, Statements, true)
ADD_CHAPTER(Basics, Variables, true)
ADD_CHAPTER(Basics, Building, true)
ADD_CHAPTER(Basics, Directives, true)
ADD_CHAPTER(Basics, Projects, true)

ADD_PART(MoreBasics, true)
ADD_CHAPTER(MoreBasics, Types, true)
ADD_CHAPTER(MoreBasics, ArithmeticTypes, true)
ADD_CHAPTER(MoreBasics, ControlFlow, true)
ADD_CHAPTER(MoreBasics, Expressions, true)
ADD_CHAPTER(MoreBasics, Introspection, true)
ADD_CHAPTER(MoreBasics, Names, true)
ADD_CHAPTER(MoreBasics, Operators, true)

ADD_PART(NotSoBasics, true)
ADD_CHAPTER(NotSoBasics, Tools, true)
ADD_CHAPTER(NotSoBasics, TypeDeduction, true)

////ADD_PROJECT(Basics, graphics, Brush, true)
//
//ADD_PROJECT(Basics, container, Ring1, true)

int main(int argc, char * argv[]) {
	//*********************************************************
	// Parse options
	//*********************************************************

	bool isUsingColor = true;
	bool isUsingFirstFail = true;
	bool isShowingHints = false;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(noColorOptionName, argv[i]) == 0) {
			isUsingColor = false;
		}
		else if (strcmp(hintsOptionName, argv[i]) == 0) {
			isShowingHints = true;
		}
		else if (strcmp(runAllOptionName, argv[i]) == 0) {
			isUsingFirstFail = false;
		}
	}

	//*********************************************************
	// Run tutorial
	//*********************************************************

	luanics::testing::tutorial::StandardReporter unfiltered(&cout, isUsingColor, isShowingHints);
	luanics::testing::tutorial::FirstFailFilter filtered(&unfiltered);
	using luanics::testing::tutorial::Reporter;
	Reporter * reporter = isUsingFirstFail ? static_cast<Reporter*>(&filtered) : static_cast<Reporter*>(&unfiltered);
	luanics::testing::tutorial::ReporterAdapter adapter(reporter);
	tutorial.run(adapter);

	return 0;
}
