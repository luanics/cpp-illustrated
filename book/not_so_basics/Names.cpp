#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>

//*********************************************************
// Namespaces
//*********************************************************

struct Person {
	std::string firstName;
	std::string lastName;
	int age;
};
struct Dog {};

namespace perez {
	Person alfonso;
	Person & daddy = alfonso;
	Person jane;  // jane declared
	Person & mommy = jane; // jane used (unqualified)
	Person elizabeth;
}

namespace smith {
	Person jane;
	Dog sneakers;
}

namespace hospital {
	Person & chiefSurgeon = ::perez::jane;
	Person & headAdministrator = ::smith::jane;
}

namespace smith {
	Person kelly;
}

//*********************************************************
// unqualified lookup
//*********************************************************

int x = 1;
namespace A {
	int y = 2;
	int b = 3;
	namespace B {
		int z = x + y;
		int a = 4;
		int b = 5;
	}
}

//*********************************************************
// unqualified lookup with using directive
//*********************************************************

namespace U {
	int a = 10;
	int y = 20;
	namespace V {
		using namespace A::B;
		int c = y + a;
		int z = y + b;
	}
}

//*********************************************************
// qualified lookup
//*********************************************************

namespace A {
	namespace C {
		int x = B::b;
	}
}

//*********************************************************
// argument dependent lookup
//*********************************************************

namespace A {
	struct S {};
	void f(S const &) {}
}

namespace U {
	void g(A::S const & s) {f(s);}
}

//*********************************************************
// Main
//*********************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Names"};

	//*********************************************************
	// Valid Names
	//*********************************************************

	// This is a valid name, but it is *reserved*!
	Person __daredevil{"Trouble", "Maker"};

	//*********************************************************
	// Scope
	//*********************************************************
	{
		// outer block
		int x = 2;
		{
			// inner block
			assert(x == 2);
			int y = 5;
			assert(y == 5);
		}
		assert(x == 2);
//		assert(y == 5); // ERROR - y not defined in this scope
	}

	//*********************************************************
	// Name Hiding
	//*********************************************************

	{
		//outer block
		int x = 2;
		{
			// inner block
			int x = 5; // hides outer x
			assert(x == 5);
		}
		// outer x unchanged
		assert(x == 2);
	}

	//*********************************************************
	// Usings
	//*********************************************************

	{
		using namespace perez; // Speaking of the Perez family ...
		elizabeth.age = 10;    // ... Lizzy just turned 10
	}

	{
		using namespace perez; // Speaking of the Perez family ...
		using namespace smith; // ... and the Smith family ...
//		jane.age = 40;         // ERROR - jane is ambiguous
	}

	{
		using perez::jane;
		jane.age = 40;
	}

	{
		using namespace perez;
		using namespace smith;
		using perez::jane;
		jane.age = 40;
	}

	//*********************************************************
	// Name Lookup
	//*********************************************************

	assert(::A::B::z == 3);

	assert(U::V::c == 25);
	assert(U::V::z == 30);

	//*******************************************************************
	// Function Name Lookup
	//*******************************************************************

//	::F1::F2::g();

	//*******************************************************************
	// ADL
	//*******************************************************************

//	O::P::g();

	//*******************************************************************
	// Swap
	//*******************************************************************

	Person mother{"Tess"};
	Person daughter{"Anna"};
	std::swap(mother, daughter);
	assert(mother.firstName == "Anna");
	assert(daughter.firstName == "Tess");


	return 0;
}
