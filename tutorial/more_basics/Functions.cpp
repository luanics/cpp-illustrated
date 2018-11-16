#include "luanics/testing/Tutorial.hpp"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <type_traits>

BEGIN_CHAPTER(Functions)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// * A pure function transforms inputs to output with no state or side effects.
// * An impure function has state and/or side effects.
// * The function signature is the function name + parameter list.
//   Informally, it may also include the return type.
// * If the function return type is not void then the function body must conclude with a return statement.
// * Parameters are input variables.
// * Arguments are expressions used to initialize the parameters.
// * Functions should normally be declared in a header file and defined in an implementation file.
// * Functions defined in a header file must be marked inline.
// * Pass-by-value: parameter holds a copy of argument --- changes to parameter leave outside world unaffected.
// * Pass-by-reference: parameter holds a reference to argument --- changes to parameter affect the outside world.
// * Read-only parameters are called in params. Read-write parameters are called in/out params.
//   * Use pass-by-ref for all in/out params.
//   * Use pass-by-const-ref for large in params.
//   * Use pass-by-const-value for small in params.
// * Default arguments provide a fallback argument expression when no argument is passed in argument list.
// * Local variables, also called automatic variables, are those defined in a function.
// * Static variables maintain their state between function calls.
// * Global variables are accessible by functions.
// * auto may be used for the return type
//   * with -> to provide a trailing return type.
//   * by itself for return type deduction.
//
///////////////////////////////////////////////////////////////////////////////

FIX(void a();)
FIX(int b(int, double const);)

SECTION(Basics) {
	// * The function signature is the function name + parameter list.
	//   Informally, it may also include the return type.

	// Change the signature of a (above) so that it takes a single int and returns a double.
	EXPECT_TRUE((std::is_invocable_r_v<double, decltype(a), int>));
	// Change the signature of b (above) so that it takes no arguments and returns void
	EXPECT_TRUE((std::is_invocable_r_v<void, decltype(b), void>));
}

FIX(int c(int & value) {value *= 2; return value;})

SECTION(PassByValue) {
	// * Pass-by-value: parameter holds a copy of argument --- changes to parameter leave outside world unaffected.

	// Modify c so that it uses pass by value
	int x = 2;
	int y = c(x);
	EXPECT_EQ(2, x);
	EXPECT_EQ(4, y);
}

FIX(void d(int value) {value *= 2;})

SECTION(PassByReference) {
	// * Pass-by-reference: parameter holds a reference to argument --- changes to parameter affect the outside world.

	// Modify d so that it uses pass by reference
	int x = 2;
	d(x);
	EXPECT_EQ(4, x);
}

FIX(void e());
FIX(void f());

SECTION(InputAndOutputParameters) {
	// * Read-only parameters are called in params. Read-write parameters are called in/out params.
	//   * Use pass-by-ref for all in/out params.
	//   * Use pass-by-const-ref for large in params.
	//   * Use pass-by-const-value for small in params.

	// Change the signature of e (above) so that it has two in/out parameters of type int and returns nothing.
	EXPECT_TRUE((std::is_invocable_r_v<void, decltype(e), int&, int&>));
	// Change the signature of f (above) so that it takes one in parameter of type int and returns an int.
	EXPECT_TRUE((std::is_invocable_r_v<int, decltype(f), int const>));
}

FIX(std::string manifesto(std::string psyche) {return "I am " + psyche;})

SECTION(DefaultArguments) {
	// * Default arguments provide a fallback argument expression when no argument is passed in argument list.

	// Modify manifesto() so that it takes a default argument of "a rock" (or another spirit animal of your choice)
	EXPECT_TRUE((std::is_invocable_r_v<std::string, decltype(manifesto), std::string>));
	EXPECT_TRUE((std::is_invocable_r_v<std::string, decltype(manifesto), void>));
}

SECTION(LocalVariables) {
	// * Local variables, also called automatic variables, are those defined in a function.

}

SECTION(StaticVariables) {
	// * Static variables maintain their state between function calls.

}

SECTION(GlobalVariables) {
	// * Global variables are accessible by functions.

}

SECTION(ReturnValues) {

}

SECTION(TrailingReturnType) {
	// * auto may be used for the return type
	//   * with -> to provide a trailing return type.

}

SECTION(ReturnTypeDeduction) {
	// * auto may be used for the return type
	//   * by itself for return type deduction.

}

END_CHAPTER(Functions)
