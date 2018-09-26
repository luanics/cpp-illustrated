#include "luanics/testing/Tutorial.hpp"

BEGIN_CHAPTER(Projects)

// * A target is a product of a build.
// * A project is a set of code-related resources along with directions for building the resources into targets.
// * While there is no generally-agreed-upon way to organize C++ projects, there are several common alternatives.
// * Even a small project will often have at least three targets:
//     An application exectutable, a test executable, and a library.
//     Adding automated documentation generation provides a fourth, doc, target.
// * A project might have multiple build configurations, such as release and debug.
// * The Luanics project is, among other things, a coding tutorial.

SECTION(Contract) {
	// I hereby certify that I have read the above documentation and understand
	//  the concepts contained within.
	EXPECT_TRUE(FIX(false))
}

END_CHAPTER(Projects)
