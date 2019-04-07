#include "luanics/testing/Tutorial.hpp"

#include <cassert>
#include <type_traits>

BEGIN_CHAPTER(References)

// * References must bind to an object exactly once, at initialization.
// * After binding, reference variables are no different than object variables --- both provide names which can be used to \emph{view} the object.
// * Different views of an object may have different types.
// * lvalue references are introduced with &, rvalue references are introduced with &&.
// * Rules for binding:
//   * lvalue references bind to objects, rvalue references to unobjects.
//   * references to non-const bind only to non-const objects, references to const bind to both const and non-const objects.
//   * As a special case, lvalue reference to const binds to everything.
// * Reference collapsing occurs when declaring a reference to a type that is aliased to a reference type.
// * Rules for reference collapsing:
//   * If either reference is lvalue, the result is lvalue.
//   * Only if both references are rvalue is the result rvalue.
//   * The resulting object type is const only if the alias is a ref-to-const.

SECTION(Basics) {
// * lvalue references are introduced with &, rvalue references are introduced with &&.
	int objectVariable = 1;
	FIX(int lvalueRefVariable) = objectVariable;
	FIX(int rvalueRefVariable) = 1;

	EXPECT_TRUE(std::is_lvalue_reference_v<decltype(lvalueRefVariable)>);
	EXPECT_TRUE(std::is_rvalue_reference_v<decltype(rvalueRefVariable)>);
}

SECTION(Binding) {
// * Rules for binding:
//   * lvalue references bind to objects, rvalue references to unobjects.
//   * references to non-const bind only to non-const objects, references to const bind to both const and non-const objects.
//   * As a special case, lvalue reference to const binds to everything.

	// Give "a" a non-const reference type that will bind to an unobject
	FIX(int a) = 1;
	EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(a)>>);
	EXPECT_TRUE(std::is_reference_v<decltype(a)>);

	// Give "b" a non-const reference type that will bind to an object
	FIX(int b) = a;
	EXPECT_FALSE(std::is_const_v<decltype(b)>);
	EXPECT_TRUE(std::is_reference_v<decltype(b)>);

	// Give "c" a const reference type that will bind to an unobject
	FIX(int c) = 1;
	EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(c)>>);
	EXPECT_TRUE(std::is_reference_v<decltype(c)>);

	// Give "d" a const reference type that will bind to an object
	FIX(int d) = c;
	EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(d)>>);
	EXPECT_TRUE(std::is_reference_v<decltype(d)>);

	// Find a common reference type for "e" and "f" that will bind to both objects and unobjects
	FIX(int e) = 1;
	FIX(int f) = e;
	EXPECT_TRUE(std::is_reference_v<decltype(e)>);
	EXPECT_TRUE(std::is_reference_v<decltype(f)>);
	EXPECT_TRUE((std::is_same_v<decltype(e), decltype(f)>));

}

SECTION(Constness) {
	//   * references to non-const bind only to non-const objects, references to const bind to both const and non-const objects.
	int const a = 1;
	// Give "b" a reference type
	FIX(int b) = a;
	EXPECT_TRUE(std::is_reference_v<decltype(b)>);
}

// We'll use this enumeration for the next section
enum class TypeCategory {
	OTHER, ///< not a reference type
	LVALUE_REF,
	LVALUE_REF_TO_CONST,
	RVALUE_REF,
	RVALUE_REF_TO_CONST
};

// Here's a function to identify which category a type is.
// Don't worry about how this works at this point - it is quite advanced.
template <typename T>
constexpr TypeCategory typeOf() {
	if constexpr (std::is_lvalue_reference_v<T>) {
		if constexpr (std::is_const_v<std::remove_reference_t<T>>) {
			return TypeCategory::LVALUE_REF_TO_CONST;
		}
		else {
			return TypeCategory::LVALUE_REF;
		}
	}
	else if constexpr (std::is_rvalue_reference_v<T>) {
		if constexpr (std::is_const_v<std::remove_reference_t<T>>) {
			return TypeCategory::RVALUE_REF;
		}
		else {
			return TypeCategory::RVALUE_REF_TO_CONST;
		}
	}
	else {
		return TypeCategory::OTHER;
	}
}

// And here is a macro to make it easier to use the function
#define REFERENCE_TYPE_OF(x) typeOf<decltype(x)>()

SECTION(ReferenceCollapsing) {
// * Reference collapsing occurs when declaring a reference to a type that is aliased to a reference type.
// * Rules for reference collapsing:
//   * If either reference is lvalue, the result is lvalue.
//   * Only if both references are rvalue is the result rvalue.
//   * The resulting object type is const only if the alias is a ref-to-const.

	using IntLvalueRef = int &;
	using IntConstLvalueRef = int const &;
	using IntRvalueRef = int &&;
	int a = 1;

	// For each of the types, choose the correct TypeCategory using the
	//  reference collapsing rules.

	IntLvalueRef b = a;
	EXPECT_EQ(REFERENCE_TYPE_OF(b), FIX(TypeCategory::OTHER));

	IntRvalueRef c = 1;
	EXPECT_EQ(REFERENCE_TYPE_OF(c), FIX(TypeCategory::OTHER));

	IntConstLvalueRef d = a;
	EXPECT_EQ(REFERENCE_TYPE_OF(d), FIX(TypeCategory::OTHER));

	IntLvalueRef & e = a;
	EXPECT_EQ(REFERENCE_TYPE_OF(e), FIX(TypeCategory::OTHER));

	IntLvalueRef const & f = a;
	EXPECT_EQ(REFERENCE_TYPE_OF(f), FIX(TypeCategory::OTHER));

	IntConstLvalueRef & g = a;
	EXPECT_EQ(REFERENCE_TYPE_OF(g), FIX(TypeCategory::OTHER));

	IntRvalueRef && h = 1;
	EXPECT_EQ(REFERENCE_TYPE_OF(h), FIX(TypeCategory::OTHER));
}

END_CHAPTER(References)
