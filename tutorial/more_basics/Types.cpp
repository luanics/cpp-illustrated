#include "luanics/testing/Tutorial.hpp" // This imports some code that we wrote

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <type_traits> // This imports some code that is part of the standard C++ library
#include <unordered_map>

BEGIN_CHAPTER(Types)

// * Types describe the general nature of their instances.
// * Common classifications of types are object-vs-non-object and fundamental-vs-compound.
// * Arithmetic types incltutorialude bool, char, int and float.
// * Pointers are objects that hold addresses.
// * References are aliases.
// * Functions are the standard named functions.
// * Closures are unnamed functions
// * Classes are standard OO components.
// * Enumerations are used for categorical data.
// * Templates generate function and class types, instantiating a new type for each set of template parameters.

SECTION(Arithmetic) {
	// "int" is an example of a C++ built-in or "fundamental" data type.
	//  A fundamental data type is part of the core C++ language and available
	//    without having to use any libraries. The C++ fundamental types
	//    represent number-ish concepts, and fall into two main categories,
	//    "integral" and "floating point". Floating point types may have a
	//    fractional part, integral types may not.
	int withoutFractionalPart = 1;
	float withFractionalPart = 1.234;

	// Additionally, some integral types may be "signed" or "unsigned".
	//   Signed types may be positive or negative, unsigned are always positive.
	unsigned int onlyPositive = 100;
	signed int positiveOrNegative = 100;
	positiveOrNegative = -100;

	// "true" and "false" values are represented using the "bool" (boolean) type
	// We can check that two values are not equal using EXPECT_NE.
	bool const iAmTrue = true;
	bool const iAmFalse = false;
	EXPECT_NE(iAmTrue, iAmFalse);
	// We will generally use the EXPECT_TRUE and EXPECT_FALSE expressions
	//  for boolean values.
	bool const iAmWrong = FIX(true);
	EXPECT_FALSE(iAmWrong);

	// ASCII characters can be stored in the "char" type:
	char const iAmA = 'a';
	char const iAm6 = '6';
	// We can check if two chars are equal.
	char const iWishIWerePunctuation = FIX('6');
	EXPECT_EQ('^', iWishIWerePunctuation);

}

SECTION(Pointers) {

}

SECTION(References) {

}

// A function that squares an integer:
int square(const int squareMe) {
	return squareMe * squareMe;
}

SECTION(Functions) {
	int const fiveSquared = square(5);
	EXPECT_EQ(FIX(9), fiveSquared);
}

SECTION(Lambdas) {

}

SECTION(Structs) {

}

SECTION(Classes) {

}

SECTION(Enumerations) {
	enum class Color{RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
	Color const dinosaur = Color::PURPLE;
	EXPECT_EQ(dinosaur, Color::GREEN);

}

namespace {

// "min" is a template function, and "T" is a template parameter.
template <typename T>
T min(T lhs, T rhs) {
	if (lhs < rhs) {
		return lhs;
	}
	else {
		return rhs;
	}
}

}

SECTION(Templates) {
	int const one = 1;
	int const two = 2;
	// Here we call min with an explicit template argument, "<int>"
	int const oneOrTwo = min<int>(one, two);
	EXPECT_EQ(0, oneOrTwo);

	double const big = 100.0;
	double const bigger = 1000.0;
	// Here the template argument is implicit and the function deduces the template arg
	//  arg types from the function arg types.
	double const bigOrBigger = min(bigger, big);
}

END_CHAPTER(Types)
