#include "luanics/testing/Tutorial.hpp"

#include <cstdint>

BEGIN_CHAPTER(FloatingPointTypes)


SECTION(Sizes) {
	// Figure out the size (in bytes) of each fp type on your system
	EXPECT_TRUE(sizeof(float) == FIX(0));
	EXPECT_TRUE(sizeof(double) == FIX(0));
	EXPECT_TRUE(sizeof(long double) == FIX(0));
}

SECTION(Literals) {
	// Figure out how to represent decimal 255 in binary, octal, hex and decimal
	EXPECT_EQ(255, FIX(0b1));
	EXPECT_EQ(255, FIX(01));
	EXPECT_EQ(255, FIX(0x1));
	EXPECT_EQ(255, FIX(1));
}

END_CHAPTER(FloatingPointTypes)
