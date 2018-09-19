#include "luanics/testing/Tutorial.hpp"

#include <type_traits>

BEGIN_CHAPTER(Introspection)

SECTION(Sizeof) {

}

SECTION(Limits) {

}

SECTION(TypeTraits) {

}

// Decltype
//
// X (input)              ->   decltype(X)  (output)
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

	// Variable names as identifiers
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(x)>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(y)>::value));
	EXPECT_TRUE((std::is_same<FIX(bool), decltype(z)>::value));

	// decltype acting on expressions is covered in Expressions.cpp
}


SECTION(TypeId) {
}

SECTION(DynamicCast) {
}

END_CHAPTER(Introspection)
