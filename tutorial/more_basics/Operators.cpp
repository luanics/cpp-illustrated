#include "luanics/testing/Tutorial.hpp"

#include <type_traits>

BEGIN_CHAPTER(Operators)

SECTION(Arithmetic) {
	// *, /, %, +, -
}

SECTION(IncrementAndDecrement) {
	// Increment, ++ can be used as either prefix or postfix operator
	int j = 1;
	int pre = ++j;
	// as a prefix the assignment to "pre" is the "new" value of j
	EXPECT_EQ(FIX(0), pre);
	EXPECT_EQ(FIX(1), (j));
	j = 1;
	int k = j++;
	// as a postfix operator the assignment to k is the "old" value of j
	EXPECT_EQ(FIX(false), (k==(j-1)));
	// of course we do not need to assign the incremented variable to anything
	// j++ = j = j+1;
	j++;
	EXPECT_EQ(FIX(2),j);

	//Decrement, --, works similarly to increment
	j = 1;
	--j;
	EXPECT_EQ(FIX(3),j);
	j = 1;
	k = j--;
	EXPECT_EQ(FIX(0),k);
	EXPECT_EQ(FIX(1),j);
}

bool logicalXor(bool const x, bool const y) {
	bool result CREATE;
	return result;
}

// TODO add, perhaps in Memory Operators the use of inc/dec with pointers
SECTION(LogicalOperators) {
	// && (and), || (or), and !(not) work on boolean, arithmetic, or pointer arguments
	const bool t = true;
	const bool f = false;
	bool r = f && t;
	EXPECT_EQ(r, FIX(true));
	// && and || evaluate second argument only if necessary
	EXPECT_EQ(t || f, FIX(false));
	EXPECT_EQ(t && !f,FIX(false));
	//Logical operators work with my types, the result of logical operator is of type boolean
	//non-zero positive integers are interpreted as true values
	int n = 7;
	EXPECT_EQ(!n, FIX(true));
	EXPECT_EQ(!true,FIX(true));
}

SECTION(BitwiseOperators) {
	// a << 2 shifts the variable "a" left (more significant bits) by 2 bit positions
	// this is equivalent to multiplying by 4
	unsigned int nv = 8;
	EXPECT_EQ(FIX(8),(nv>>1));
	// similarly, a>>2 shifts the variable "a" to the right by 2 bit positions
	// This is equivalent to dividing by 4
	nv = nv >> 1;
	EXPECT_EQ(FIX(16),(nv<<1));

	// bitwise operators & (and), | (or), ^ (exclusive or), and ~ complement
	// have interesting uses which will be addressed in more advanced topics
	// for now we are focused on the mechanics of these operators
	int a = 0xFF;
	int b = 0x4;
	int c = 0b11111011;
	int d = 0xFFFB;
	EXPECT_EQ(FIX(0x00),(b|c));
	EXPECT_EQ(FIX(0x00),(a&b));
	// xor is also called the symmetric difference
	// since b = ~d the symmetric difference is 0xFFFF
	EXPECT_EQ(FIX(0xFFFF),(b^d));
	EXPECT_EQ(FIX(0x0),a^b);
	// bitwise operators may be used with arguments other than just int or unsigned int
	// These will be covered in later topics
}

SECTION(ConditionalExpressions) {
	// the conditional expression, a ? b : c, yields "b" if "a" (a boolean)
	// evaluates to true and "c," otherwise
	int a = 7;
	int b = 12;
	int max = (a<b)?b:a;
	EXPECT_EQ(FIX(a),max);
}

SECTION(Assignment) {
	// =, *=, /=, +=, -=, %=
}

SECTION(Relational) {
	// <, <=, >, >=, ==, !=
}

SECTION(Precedence) {
	// Precedence is not a issue for most clean code, however there
	// are cases where ignoring precedence will produce unexpected results
	// Consider a few examples
	int k = 1, j = 1, m = 1, n = 1;
	int o = 0;

	bool b1 = !k;
	bool b2 = !--k;
	bool b3 = !j--;
	bool b4 = !m++;
	bool b5 = !++n;
	bool b6 = !o++;

	EXPECT_EQ(b1,FIX(true));
	EXPECT_EQ(b2,FIX(false));
	EXPECT_EQ(b3,FIX(true));
	EXPECT_EQ(b4,FIX(true));
	EXPECT_EQ(b5,FIX(true));
	EXPECT_EQ(b6,FIX(false));

	bool v = true;

	int r = !v ? 2 : 3;
	EXPECT_EQ(r,FIX(2));
	r = !(v ? 2 : 3);
	EXPECT_EQ(r,FIX(true));
	n = 1;
	r = v ? ++n : 4;
	EXPECT_EQ(r,FIX(4));
}

END_CHAPTER(Operators)
