#include "luanics/testing/Tutorial.hpp" // This imports some code that we wrote

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <type_traits> // This imports some code that is part of the standard C++ library
#include <unordered_map>

BEGIN_CHAPTER(Types)

// * Types describe the nature of their instances.
// * Common classifications of types are object-vs-non-object and fundamental-vs-compound.
// * C++ is a statically-typed language because the type of all objects is fixed at compile time.
// * C++ is a weakly-typed language because it supports implicit conversions in addition to explicit conversions.
// * void is a special type that is used in certain contexts to indicate the absence of type.
// * Arithmetic types include bool, char, integral and floating point.
// * Pointers are objects that hold addresses.
// * Arrays hold a homogeoneous sequence.
// * References are aliases for objects.
// * Functions are reusable blocks of code. A simple function will receive data as input and return data as output.
// * Closure types are unnamed functions defined by lambda expressions and producing objects called closures.
// * User-defined types include structs, classes, unions and enums. Generally speaking,
//   * Structs store state in member variables.
//   * Classes store state in member variables and provide behavior through member functions.
//   * Unions have one member variable active at a time.
//   * Enumerations represent categorical data.
// * Templates generate function and class types, instantiating a new type for each set of template parameters.

class Person {
public:
	Person(std::string name) : _name{std::move(name)} {}
	std::string const & name() const {return _name;}
private:
	std::string _name;
};

SECTION(StaticButWeak) {
	// * C++ is a statically-typed language because the type of all objects is fixed at compile time.


	// * C++ is a weakly-typed language because it supports implicit conversions in addition to explicit conversions.
	int one = 1;
	double alsoOne = FIX(0.0); // Set me to "one"
	EXPECT_EQ(1.0, alsoOne);

	// But not everything is implicitly convertable.
//	int definitelyNotOne = george; // Uncommenting this line causes error.
}

int f(void) {return 1;}

SECTION(Void) {
	// * void is a special type that is used in certain contexts to indicate the absence of type.
	EXPECT_EQ(FIX(0), f());
}

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
	// * Pointers are objects that hold addresses.
	int x = 5;
	int * ptr = &x; // Take the address of x with &
	EXPECT_EQ(FIX(0), *ptr); // Obtain the value with *
}

SECTION(ArrayTypes) {
	// * Arrays hold a homogeoneous sequence.
	// Zero-based access is performed with the subscript operator, [].

	int primes[] = {2, 3, 5, 7, 11};
	EXPECT_EQ(FIX(3), FIX(primes[0]));
	EXPECT_EQ(5, primes[FIX(0)]);
}

SECTION(References) {

}

// A function that squares an integer:
int square(int const squareMe) {
	return squareMe * squareMe;
}

SECTION(Functions) {
	// * Functions are reusable blocks of code. A simple function will receive data as input and return data as output.
	int const fiveSquared = square(5);
	EXPECT_EQ(FIX(9), fiveSquared);
}

SECTION(Closures) {
	// * Closure types are unnamed functions defined by lambda expressions and producing objects called closures.
	auto square = [](int const squareMe){return FIX(squareMe);};
	EXPECT_EQ(25, square(5));
}

struct Typer1 {
	std::string _name; // state
	int _wpm; // state
};

SECTION(Structs) {
	//   * Structs store state in member variables.
	Typer1 dave{"dave", 100};
	EXPECT_EQ(FIX(90), dave._wpm);

	Typer1 danielle{FIX()};
	EXPECT_EQ("danielle", danielle._name);
	EXPECT_EQ(80, danielle._wpm);
}

class Typer2 {
public:
	Typer2() = default;
	Typer2(std::string name, int const wpm) : // behavior
		_name{std::move(name)},
		_wpm{wpm}
	{}
	std::string const & name() const {return _name;} // behavior
	int wpm() const {return _wpm;} // behavior
	void train() {_wpm += 20;} // behavior
private:
	std::string _name; // state
	int _wpm; // state
};

SECTION(Classes) {
	//   * Classes store state in member variables and provide behavior through member functions.
	Typer2 dave{"dave", 100};
	EXPECT_EQ(FIX(90), dave.wpm());

	Typer2 danielle{FIX()};
	EXPECT_EQ("danielle", danielle.name());
	EXPECT_EQ(80, danielle.wpm());
	danielle.train();
	EXPECT_EQ(FIX(80), danielle.wpm());
}

union TyperGoal {
	int _wpm;
	double _accuracy;
};

SECTION(Union) {
	//   * Unions have one member variable active at a time.
	TyperGoal goal;
	goal._wpm = 70;
	EXPECT_EQ(FIX(60), goal._wpm);
//	EXPECT_EQ(?, goal._accuracy); // _accuracy not defined at this point
	goal._accuracy = 0.99;
	EXPECT_NEAR(0.90, goal._accuracy);
//	EXPECT_EQ(?, goal._wpm); // _wpm not defined at this point
}

SECTION(Enumerations) {
	//   * Enumerations represent categorical data.
	enum class Color{RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
	Color const dinosaur = Color::PURPLE;
	EXPECT_EQ(dinosaur, FIX(Color::GREEN));
}

namespace {

// "min" is a function template, and "T" is a template parameter.
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
	// * Templates generate function and class types, instantiating a new type for each set of template parameters.

	int const one = 1;
	int const two = 2;
	// Here we call min with an explicit template argument, "<int>"
	int const oneOrTwo = min<int>(one, two);
	EXPECT_EQ(FIX(0), oneOrTwo);

	double const big = 100.0;
	double const bigger = 1000.0;
	// Here the template argument is implicit and the function deduces the template arg
	//  arg types from the function arg types.
	double const bigOrBigger = min(bigger, big);
	EXPECT_NEAR(FIX(0.0), bigOrBigger);
}

END_CHAPTER(Types)
