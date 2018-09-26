#include "luanics/testing/Tutorial.hpp" // This imports some code that we wrote

#include <cstring>
#include <string>

BEGIN_CHAPTER(Directives)

// * Directives are commands for the preprocessor.
// * There are roughly five categories of directive:
//   * text replacement - macros
//   * text selection - conditional compilation
//   * text insertion - #include
//   * compiler error - #error
//   * compiler specific - #pragma
// * #define introduces macro directives, #undef removes them.
// * Object-like macros replace the macro name with the body.
// * Function-like macros replace macro name with body, while substituting in arguments.
// * To make macros place nice, use parens twice.
// * Prefer variables and functions to macros.
// * Inside a macro body, # does stringizing while ## does token pasting.
// * Predefined macros like __FILE__ insert information about the context.
// * To avoid collision between libraries, macro names should be prefixed with the name of the library.

SECTION(Macros) {
	// * #define introduces macro directives, #undefine removes them.
	// * Object-like macros replace the macro name with the body.
	// * Function-like macros replace macro name with body, while substituting in arguments.

	// Start by fixing the object-like macro, LEVEL
	#define LEVEL FIX(10)
	EXPECT_EQ(11, LEVEL)
	#undef LEVEL // cleanup

	// Now try an object-like macro, SCALE(x), that does 2*x + 1
	#define SCALE(x) FIX(0)
	EXPECT_EQ(1, SCALE(3))
	EXPECT_EQ(2, SCALE(5))
}

SECTION(MacroPitfalls) {
	// * To make macros place nice, use parens twice.
	// For example
	#define DOUBLE(x) (2*(x))
	#undef DOUBLE

	// Did you remember the parentheses when defining INCREMENT(x)?
	// In Eclipse, use Ctrl+= to see the macro expansion.
	EXPECT_EQ(15, SCALE(1)*SCALE(2))
	EXPECT_EQ(5, SCALE(1+1))
}

SECTION(PreprocessorOperators) {
	// * Inside a macro body, # does stringizing while ## does token pasting.
	// So, with this definition
	// #define STRINGIZE(x) #x
	// we find that
	// STRINGIZE(hi)
	// is replaced with "hi"

	// Define a function-like macro called CONCATENATE(x,y) that stringizes
	//  the arguments together.
	#define CONCATENATE(x,y) FIX("")
	EXPECT_EQ(0, std::strcmp("hithere", CONCATENATE(hi,there)))

	// The preprocessor will join adjacent string literals, like
	//  "x" "y"
	//  into a single string literal, like
	//  "xy"
	// Define a function-like macro called PIG_LATINATE(x) that stringizes
	//  x with the string "nay" appended
	#define PIG_LATINATE(x) FIX("")
	EXPECT_EQ(0, std::strcmp("hinay", PIG_LATINATE(hi)))
}

SECTION(StandardPredefinedMacros) {

}

SECTION(ConditionalCompilation) {
	// Use a preprocessor directive to define the macro LOVE
	CREATE

	#ifdef LOVE
		EXPECT_REACHED();
	#else
		EXPECT_NOT_REACHED();
	#endif

	// Now use a preprocessor directive to "cleanup" and undefine LOVE
	CREATE

	#ifndef LOVE
		EXPECT_REACHED();
	#else
		EXPECT_NOT_REACHED();
	#endif
}

SECTION(NameDecoration) {
	// * To avoid collision between libraries, macro names should be prefixed with the name of the library.

}

END_CHAPTER(Directives)
