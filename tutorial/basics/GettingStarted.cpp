// Hi! Welcome to the "luanics" C++11 tutorial. This is a comment line.

// Here are some "include directives" that import some code...
#include "../../luanics/crypto/VigenereCipher.hpp"
#include "luanics/testing/Tutorial.hpp"

// Each chapter of the tutorial is in a difference .cpp (source) file,
//  and has "BEGIN_CHAPTER" near the top. This chapter is called
//  "GettingStarted". This is the first chapter of the "Basics"
//  part of the tutorial.
// Note that "BEGIN_CHAPTER" is not part of the C++ language
//  - it is a C++ "macro" that we wrote as part of the implementation
//  of the tutorial framework.
//  You should be able to spot most macros because, by convention, they
//  are written in SCREAM_CASE.
//  If you're using an advanced IDE like Eclipse or VisualStudio,
//  you should see an expansion of the macro if you hover over it.
//  Don't worry about the details for now, though.
BEGIN_CHAPTER(GettingStarted)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	GettingStarted
//
// * Most chapters begin with a brief overview of the material covered.
//   This is a hands-on tutorial, though, so most of the learning will
//   occur through "Doing" as you work through the code examples. There are two
//   types of Doing in the tutorial: "Fixing" and "Creating".
//   1) Fixing will require you to modify existing code to produce the correct
//      result. Code that needs to be fixed will usually be contained in a "FIX"
//      statement. If you see "FIX(x)", you need to replace the incorrect
//      expression, x, with a correct expression.
//   2) Creating will require you to write original code. You'll see the
//      "CREATE" statement wherever Creating is needed. You should remove
//      the "CREATE" and replace it with your own code.
//
// * Here's how we suggest you make your way through the tutorial:
//   1. From a command line terminal, enter the `luanics/build/release` directory
//   2. Run `cmake ../..` to *configure* the project
//   3. Run `make` to *compile* the project
//   4. Run the tutorial from the command line (`../../bin/tutorial` in linux)
//      - When run, the tutorial will show your progress and provide the file
//         and line number of the next challenge you should work on.
//   4 Work on the next challenge.
//   5 Goto 3
//
// * Go ahead and do steps 1-3 now. The output will point you to the next
//   challenge below. See you there!
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// This is the "Fixing" section of the "GettingStarted" chapter. SECTION is another
//  macro we wrote.
SECTION(Fixing) {
	// There are several types of "EXPECT" statements in the tutorial.
	// When something is not yet fixed, the EXPECT_ statements will report it
	//  as a problem when the tutorial is run.

	// We use the EXPECT_TRUE macro to indicate that an expression should be true.
	// Fix this by replacing "false" with "true"
	EXPECT_TRUE(FIX(false));

	// "true" and "false" are the possible values of "boolean" variables.
	EXPECT_FALSE(FIX(true));

	// EXPECT_EQ(a, b) means we expect a to be Equal to b
	EXPECT_EQ(2, FIX(3));

	// EXPECT_NE(a, b) means we expect a to be Not Equal to b
	EXPECT_NE(2, FIX(2));
}

int multiply(int const a, int const b) {
	// Replace the CREATE below with: return a * b;
	CREATE
}

SECTION(Creating) {
	// Creating often occurs inside functions. Create code in the "multiply"
	//  function above.
	EXPECT_EQ(6, multiply(3,2));
}

SECTION(Printing) {
	// One more thing. If you want to have the tutorial print something out
	//   you can use the PRINT(x) macro. Like this:
	auto const message = "Hi, I'm a log message!";
	PRINT(message);

	// Here's some cryptography...
	luanics::crypto::VigenereCipher cipher("luanics");
	auto const decodedMessage = cipher.decrypt("dycemvk");
	// This PRINT message prints the decoded message.
	PRINT(decodedMessage);
	// Find the decoded message in the tutorial output and enter it here to pass
	EXPECT_EQ(decodedMessage, FIX(""));
}

// That's it for "GettingStarted"! See you in the next chapter, "Stat...

END_CHAPTER(GettingStarted)
