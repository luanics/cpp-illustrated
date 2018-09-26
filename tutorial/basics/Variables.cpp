#include "luanics/testing/Tutorial.hpp" // This imports some code that we wrote

#include <string>

BEGIN_CHAPTER(Variables)

// * A variable is a place to store information along with a name used to retrieve the information.
// * The information is called the value and the place it is stored is an object.
// * Type determines the values a variable can take and how it can be manipulated.
// * A variable definition has a type, an identifier, and an optional initializer.
// * A variable is either an object variable or a reference variable.
// * Reference variables are aliases.
// * Use the "const" keyword to prevent a variable from being modified.
// * Use the "auto" keyword for type inference.
// * There are several forms of initialization.
//   * Leaving out the initializer is a form of initialiation --- default initialization.
//   * An initializer with = is copy initialization (not assignment),
//     without is direct initialization.
//   * An initializer with braces is list initialization,
//     without is no-list initialization.

SECTION(Basics) {
	// * A variable definition has a type, an identifier, and an optional initializer.

	// Add initializers to the following variable declarations to pass.
	int wrong FIX();
	int right = 10;
	EXPECT_EQ(right, wrong + wrong);

	std::string test FIX();
	std::string hi FIX();
	std::string bye FIX();
	std::string const hiAndBye = hi + "and" + bye;
	EXPECT_EQ("hi and bye", hiAndBye);

	// * Reference variables are aliases.

	// The variables above are object variables. Adding "&" makes a reference
	//  variable, so that it "refers" to another variable, like an alias.
	int a = 10;
	int & b = a;
	b = 20;
	EXPECT_EQ(FIX(10), a);

	// Make "y" a reference variable that refers to "x":
	int x = 1;
	FIX(int y);
	y = 2;
	EXPECT_EQ(2, x);
}

SECTION(Constness) {
	// * Use the "const" keyword to prevent a variable from being modified.

	// const variables are set to the appropriate value at initialization, and
	//   cannot be changed after that.
	int const one = 1;
	// Try uncommenting the following line and compiling.
	// one = 2;
	// Get into the habit of reading variable declarations from left-to-right:
	// "one is a variable of const int type"

	// If you know that the value of a variable should not be changed,
	//   MAKE IT CONST. This way, the compiler will give you an error if it is
	//   misused.
	// From their names, it is obvious that these variables should not have their
	//   value changed, so we'll make them const.
	int const two = 2;
	int const three FIX(=2);

	// const variables can also be used on the right-hand-side of an equal sign
	int const four = two + two;
	EXPECT_EQ(FIX(three), two + two);

	// The const can also be put on the left side of the type...
	const int five = 5;
	//   but then it is harder to read it from right to left.
}

SECTION(TypeDeduction) {
	// * Use the "auto" keyword for type inference.

	// Replace the explicit type specification with type deduction:
	FIX(std::string) name = "Scooby";
	EXPECT_EQ("Scooby", name);
}

SECTION(Initialization) {
	// * There are several forms of initialization.

	// Use "value initialization" to set zero to 0
	int const zero{FIX(0)};
	EXPECT_EQ(0, zero);
	// Use "direct list initialization" to set one to 1
	int const one{FIX()};
	EXPECT_EQ(1, one);
	// Use "direct no-list initialization" to set two to 2
	int const FIX(two{});
	EXPECT_EQ(2, two);
	// Use "copy list initialization" to set three to 3
	int const three = {FIX()};
	EXPECT_EQ(3, three);
	// Use "copy no-list initialization" to set four to 4
	int const four = FIX(0);
	EXPECT_EQ(4, four);
}

END_CHAPTER(Variables)
