#include "luanics/testing/Tutorial.hpp"

#include <type_traits>

BEGIN_CHAPTER(Introspection)

// * Reflection concerns types instead of variables, and consists of introspection (query) and intercession (modification).
// * C++ supports full reflection at compile time, but only introspection at run time.
// * The tools of compile time introspection include:
//	 * static_assert: a compile-time assertion
//	 * type_traits: queries about the categories and capabilities of types
//	 * numeric_limits: queries about the numeric properties of types
//	 * unevaluated contexts: safe zones for hypothetical expressions
//	 * sizeof: query for the size of types
//	 * decltype: get the type of an expression
// * The unevaluated contexts are the sizeof operator and the decltype and noexcept specifiers.
// * The tools of run-time introspection include:
//	 * typeid: determine the type of an object
//	 * dynamic_cast: safely cast to subclass
// * Prefer compile-time assertions (static_assert) to run-time assertions (assert).

SECTION(CompileTimeIntrospection) {

}

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
