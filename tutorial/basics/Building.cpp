#include "luanics/testing/Tutorial.hpp"

#include <cassert>

BEGIN_CHAPTER(Building)

SECTION(Macros) {
#define LEVEL FIX(3)
	EXPECT_EQ(LEVEL, 4)
#undef LEVEL // cleanup
}

SECTION(ConditionalCompilation) {
// Use a preprocessor directive to define the macro LOVE
CREATE

#ifdef LOVE
	EXPECT_REACHED();
#else
	EXPECT_NOT_REACHED();
#endif

// Now use a preprocessor directive to "cleanup" and undefine LOVE
CREATE

#ifndef LOVE
	EXPECT_REACHED();
#else
	EXPECT_NOT_REACHED();
#endif
}

SECTION(BrokenCode) {
// Sometimes we use conditional compilation to "turn off" code with errors
//  until you are ready to work on it.
//	When you are ready, uncomment the line "#define IS_ACTIVE" to begin.
//#define IS_ACTIVE
#ifdef IS_ACTIVE
	EXPECT_REACHED();
#endif
	EXPECT_NOT_REACHED();
#undef IS_ACTIVE
}

SECTION(IncludeFiles) {
// Uncomment to begin...
//#define IS_ACTIVE
#ifdef IS_ACTIVE
// Uncomment the correct line to win the grand prize...
//#include "data/DoorA.hpp"
//#include "data/DoorB.hpp"
//#include "data/DoorC.hpp"
	EXPECT_EQ("new car", prize())
#endif
	EXPECT_NOT_REACHED();
#undef IS_ACTIVE
}

END_CHAPTER(Building)
