#include "luanics/testing/Tutorial.hpp"

#include <type_traits>

BEGIN_CHAPTER(Expressions)

// As a reminder...
// Decltype
//
// X (input)                    ->  decltype(X)  (output)
// =================================================
// identifier of type T         ->  T
// -------------------------------------------------
// xvalue expression of type T  ->  T&&
// lvalue expression of type T  ->  T&
// prvalue expression of type T ->  T
// =================================================
SECTION(Decltype) {
	int x = 1;
	int const y = 2;
	int const & z = x;

	// From Introspection.cpp: Variable names as identifiers
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(x)>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(y)>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(z)>::value));

	// Variable names as expressions
	EXPECT_TRUE((std::is_same<FIX(bool), decltype((x))>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype((y))>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype((z))>::value));

	// Other expressions
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(std::move(x))>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(x + x)>::value));
}

SECTION(Literals) {
	// What is the type of a literal expression? Note that it is NOT const
	EXPECT_TRUE((std::is_same<FIX(int const), decltype(4)>::value));
}

END_CHAPTER(Expressions)
