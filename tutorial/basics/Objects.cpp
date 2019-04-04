#include "luanics/testing/Tutorial.hpp"

BEGIN_CHAPTER(Objects)

// * An object is both
//   * a region in storage that represents state.
//   * an instance of a type.
// * The attributes of an object are type and storage.
// * A value is an interpretation of bits via a type.
// * A variable is a name-object pair.
// * At definition, object variables bind a name to a new object,
//    while reference variables bind a name to an existing object.
// * After definition, object variables and reference variables are equivalent ---
//    just names referring to objects.
// * Elements with value are valuables. They can be objects or unobjects.
// * Objects require formal construction, unobjects do not.
// * A view is a way of referring to an valuable. A view can be named or unnamed, and has an associated type.
// * Testing objects for equality compares values. Testing objects for identity compares locations.

SECTION(References) {
// * At definition, object variables bind a name to a new object,
//    while reference variables bind a name to an existing object.

	int a = 1;
	EXPECT_EQ(1, a);
	int & b = a;
	EXPECT_EQ(1, b);
	a = 2;
	EXPECT_EQ(2, b);

	// Change c from an object variable to a reference variable that binds to a
	FIX(int c) = a;
	EXPECT_EQ(2, c);
	a = 3;
	EXPECT_EQ(3, c);
}

SECTION(Identity) {
	// Objects are "equal" if they hold the same value.
	// Make these two variables equal:
	int a = 4;
	int b = FIX(5);
	EXPECT_EQ(a, b);

	// Objects are "identical" if they have the same address
	// Make these two variables identical
	int c = 5;
	int FIX(d = 5);
	EXPECT_EQ(&c, &d);
}

END_CHAPTER(Objects)
