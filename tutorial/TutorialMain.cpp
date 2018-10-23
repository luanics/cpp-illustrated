#include "luanics/testing/core/FirstFailFilter.hpp"
#include "luanics/testing/core/IndentingReporter.hpp"
#include "luanics/testing/core/ReporterAugmenter.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>

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
		else if (strcmp(helpOptionName, argv[i]) == 0) {
			std::cout << "C++ Illustrated Tutorial" << std::endl;
			std::cout << "options:";
			std::copy(begin(optionNames), end(optionNames), ostream_iterator<const char *>(std::cout, ","));
			std::cout << std::endl;
			return 0;
		}
	}

	//*********************************************************
	// Run tutorial
	//*********************************************************

	luanics::testing::core::IndentingReporter unfiltered(&cout, isUsingColor, isShowingHints);
	luanics::testing::core::FirstFailFilter filtered(&unfiltered);
	using luanics::testing::core::AugmentedReporter;
	AugmentedReporter * reporter = isUsingFirstFail ? static_cast<AugmentedReporter*>(&filtered) : static_cast<AugmentedReporter*>(&unfiltered);
	luanics::testing::core::ReporterAugmenter augmenter(reporter);
	tutorial.run(augmenter);

	return 0;
}
