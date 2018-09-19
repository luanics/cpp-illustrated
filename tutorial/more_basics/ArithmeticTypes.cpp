#include "luanics/testing/Tutorial.hpp"

#include <cstdint>

BEGIN_CHAPTER(ArithmeticTypes)

SECTION(Sizes) {
	// Figure out the size (in bytes) of each arithmetic type on your system
	EXPECT_TRUE(sizeof(char) == FIX(0));
	EXPECT_TRUE(sizeof(bool) == FIX(0));
	EXPECT_TRUE(sizeof(short int) == FIX(0));
	EXPECT_TRUE(sizeof(int) == FIX(0));
	EXPECT_TRUE(sizeof(long int) == FIX(0));
	EXPECT_TRUE(sizeof(long long int) == FIX(0));
	EXPECT_TRUE(sizeof(float) == FIX(0));
	EXPECT_TRUE(sizeof(double) == FIX(0));
}

SECTION(Literals) {
	// Figure out how to represent decimal 255 in binary, octal, hex and decimal
	EXPECT_EQ(255, FIX(0b1));
	EXPECT_EQ(255, FIX(01));
	EXPECT_EQ(255, FIX(0x1));
	EXPECT_EQ(255, FIX(1));
}

END_CHAPTER(ArithmeticTypes)
