#include "luanics/utility/Herald.hpp"

#include <cassert>

int main() {
	luanics::utility::Herald herald{"References"};

	//*********************************************************
	// Binding
	//*********************************************************

	int a = 2;

	int & goodLref = a;  // OK - bind to object, a
//	int & badLref = 2;   // ERROR - can't bind to unobject, 2

	int && goodRref = 2; // OK - bind to unobject, 2
//	int && badRref = x;  // ERROR - can't bind to object, a

	int & lref = a;
	int && rref = 2;

	int b = 3;
	b = lref; // OK - b equals 2
	b = rref; // OK - b still equals 2

	lref = 2; // OK - Sets lref (and a) to 2
	rref = 4; // OK - Sets rref to 4

//	int & badRef;      // ERROR - must bind at initialization
	int & goodRef = a; // OK
	goodRef = b;       // OK, but this is assignment, *not* rebinding

	//*********************************************************
	// Constness
	//*********************************************************

	int const c = 4;
//	int & refToNonConst = c;            // ERROR - need "ref to const", not "ref"
	int const & refToConst = c;         // OK
//	int & const constRefToNonConst = z; // ERROR - "const ref" not valid

	int d = 5;
	int const & dref = d;
	d = 6;     // OK - d has "int" view of the object
	assert(d == 6);
	assert(dref == 6);
//	dref = 7;  // ERROR - dref has "const int" view of the object

	int const e = 8;
	int & eref = const_cast<int &>(e);

	//*********************************************************
	// Eager Evaluation
	//*********************************************************

	int f = 9;
	int && g = 2 + f; // Eager evaluation sets g to 11
	f = 10;
	assert(f == 10);
	assert(g == 11);  // Lazy evaluation would set g to 10

	//*********************************************************
	// Pitfalls
	//*********************************************************

	int i = 11;
	int const & iref = i;
	assert(i == 11 and iref == 11);
	i = 12;
	assert(i == 12 and iref == 12); // i and iref refer to same object

	char j = 13;
	int const & jref = j;
	assert(j == 13 and jref == 13);
	j = 14;
	assert(j == 14 and jref ==13); // j and jref refer to different objects

	return 0;
}
