#include "luanics/testing/Tutorial.hpp"

BEGIN_CHAPTER(Tools)

SECTION(ToolActivation) {
// Activate the tools by editing luanics/CMakeLists.txt to define the following:
// LUANICS_LEAK_CHECKING
// LUANICS_LOGGING
// LUANICS_PROFILING

#ifdef LUANICS_LEAK_CHECKING
	EXPECT_REACHED();
#else
	EXPECT_NOT_REACHED();
#endif

#ifdef LUANICS_LOGGING
	EXPECT_REACHED();
#else
	EXPECT_NOT_REACHED();
#endif

#ifdef LUANICS_PROFILING
	EXPECT_REACHED();
#else
	EXPECT_NOT_REACHED();
#endif

}

END_CHAPTER(Tools)
