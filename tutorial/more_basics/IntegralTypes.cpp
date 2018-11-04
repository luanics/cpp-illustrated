#include "luanics/testing/Tutorial.hpp"

#include <cstdint>
#include <iomanip>
#include <sstream>

BEGIN_CHAPTER(IntegralTypes)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Integral Types
//
// * Arithmetic types include both integral and floating-point types.
// * The smallest unit of computer memory is the bit.
// * In most implementations a byte is eight bits.
// * While the machine uses binary (base-2) representation, C++ supports
//   binary (base-2), octal (base-8), decimal (base-10), and hexadecimal/hex (base-16).
//   * Literals can be written in non-decimal bases using special prefixes:
//     0b (binary), 0 (octal), 0x (hex). Any integer literal not starting with '0' is decimal.
//   * Literals can be displayed in different bases using special io manipulators:
//     std::oct (octal), std::dec (decimal), std::hex (hex).
// * Integers may be represented with multiple bytes.
// * The sizeof operator may be used to determine the number of bytes taken by a type or expression.
// * Endianness refers to the arrangement of bytes in a multi-byte type.
// * The integral types are bool, char, and int and their variants.
//   * bool is an integral type that can only take on the values true and false.
//   * char is an integral type used to represent single text characters.
//   * int is an integral type used to represent integral numbers.
// * Integral types take optional size and sign modifiers.
//   * The sign modifiers, which may be applied to \Type{char} and \Type{int}, are \Keyword{signed} and \Keyword{unsigned}.
//   * The size modifiers, which may only be applied to \Type{int}, are \Keyword{short}, \Keyword{long}, and \Keyword{long long}.
// * In many 64-bit implementations an \Type{int} is 4-bytes long.
// * Because the meanings of the size modifiers are implementation dependent, \emph{integral aliases} are provided when specific sizes are required.
// * Common integral pitfalls include unsigned \emph{wrapping}, signed \emph{overflow}, signed-to-unsigned \emph{conversion}, and division by zero.
//   * Wrapping and overflow occur when an operation results in a value that lies outside of the range representable by the integral type.
//   * Wrapping is well-defined behavior, acting as we expect from modulo arithmetic.
//   * Overflow is undefined behavior.
//   * Signed-to-unsigned conversion occurs when using mixed-signed arithmetic. It is well-defined, but error-prone.
//   * Division by zero is undefined behavior.
//
///////////////////////////////////////////////////////////////////////////////

SECTION(Bases) {
	// Figure out how to represent decimal 255 in binary, octal, decimal, and hex
	EXPECT_EQ(255, FIX(0b1));
	EXPECT_EQ(255, FIX(01));
	EXPECT_EQ(255, FIX(1));
	EXPECT_EQ(255, FIX(0x1));

	// Display 10 in different bases using io manipulators
	int const ten = 10;
	std::ostringstream decOut;
	decOut << ten;
	EXPECT_EQ("10", decOut.str());

	std::ostringstream octOut;
	octOut << FIX(std::dec) << ten;
	EXPECT_EQ("12", octOut.str());

	std::ostringstream hexOut;
	hexOut << FIX(std::dec) << ten;
	EXPECT_EQ("a", hexOut.str());
}

SECTION(MultiByteTypes) {
	// Figure out the size (in bytes) of each integral type on your system
	EXPECT_TRUE(sizeof(bool) == FIX(0));
	EXPECT_TRUE(sizeof(char) == FIX(0));
	EXPECT_TRUE(sizeof(int) == FIX(0));
}

SECTION(IntegralTypes) {
	//   * bool is an integral type that can only take on the values true and false.
	bool const isExamPassed = FIX(false);
	bool const areAssignmentsCompleted = FIX(true);
	bool const isPassing = isExamPassed and areAssignmentsCompleted;
	EXPECT_TRUE(isPassing);

	//   * char is an integral type used to represent single text characters.
	char const letter1 = 'D';
	char const letter2 = FIX('D');
	EXPECT_LT(letter1, letter2);

	//   * int is an integral type used to represent integral numbers.
	int const grade1 = 90;
	int const grade2 = 70;
	int const grade3 = FIX(80);
	int const averageGrade = (grade1 + grade2 + grade3) / 3;
	EXPECT_TRUE(averageGrade >= 85);

	// Figure out the size (in bytes) of each modified int type on your system
	EXPECT_TRUE(sizeof(short int) == FIX(0));
	EXPECT_TRUE(sizeof(int) == FIX(0));
	EXPECT_TRUE(sizeof(long int) == FIX(0));
	EXPECT_TRUE(sizeof(long long int) == FIX(0));
}

END_CHAPTER(IntegralTypes)
