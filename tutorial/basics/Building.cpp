#include "luanics/testing/Tutorial.hpp"

#include <cassert>

BEGIN_CHAPTER(Building)

// * A build refers to one complete iteration of the build process.
// * The main stages of the build process are preprocessor, compiler, assembler and linker.
// * Pitfall - people often use "compiling" to mean "building", and "compiler" to mean "build system".
// * Source code is typically divided up into header files (.hpp) for the interface, and source files (.cpp) for the implementation
// * The preprocessor produces a translation unit from a source file by inserting all "included" headers into the source file.
//   Include guards are used to prevent multiple insertion of the same file.
// * Build management tools coordinate the build, providing an easier build experience for the user. We use the CMake build management tools.

#include "data/CommentMeOutToPlay.hpp"
//#include "data/DoorA.hpp"
//#include "data/DoorB.hpp"
//#include "data/DoorC.hpp"

SECTION(IncludeFiles) {
	// * The preprocessor produces a translation unit from a source file by inserting all "included" headers into the source file.
	// Uncomment the correct line above to win the grand prize...
	EXPECT_EQ("new car", prize());
}

END_CHAPTER(Building)
