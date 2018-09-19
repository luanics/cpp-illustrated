#include "luanics/testing/Tutorial.hpp"

BEGIN_CHAPTER(ControlFlow)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Control Flow Statements
//
// * "Control flow" is the path (flow) of execution.
// * Control flow types are "sequential", "selection" and "iteration" and "jump".
// * Sequential is default control flow - each statement executed consecutively.
// * Use a control flow statement to alter control flow from sequential.
// * Selection control flow statements include "if-else" and "switch".
// * Iteration control flow statements include "for", "while", and "do-while".
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Sequential is default control flow
SECTION(Sequential) {
	// Obviously, executing these statements in a non-sequential order would
	//  change the result.
	int x = 2;
	x += 2;
	x *= 5;
	x /= 2;
	EXPECT_EQ(FIX(0), x);
}

// "If" is the workhorse of selection control statements.
SECTION(If) {
	bool isAcOn = false;
	double temp = 90.0;
	if (temp > 75) {
		CREATE
	}
	EXPECT_TRUE(isAcOn);
}

// "If-Else" is a bit fancier
SECTION(IfElse) {
	bool likesGarlic = true;
	std::string team("vampire");
	if (likesGarlic) {
		team.insert(0,"is not ");
	} else {
		team.insert(0,"is ");
	}
	EXPECT_EQ("is or is not vampire",team);
}

// The queen of ifs
SECTION(IfElseIf) {
	int acLevel = 0;
	double temp = FIX(50.0);
	if (temp < 70.0) {
		acLevel = 0;
	}
	else if (temp < 80.0) {
		acLevel = 1;
	}
	else if (temp < 90.0) {
		acLevel = 2;
	}
	else {
		acLevel = 3;
	}
	EXPECT_EQ(FIX(1), acLevel);
}

// The "ternary operator", "?", provides selection between two alternatives.
SECTION(Ternary) {
	bool likesGarlic = FIX(false);
	std::string team = likesGarlic ? "Jacob" : "Edward";
	EXPECT_EQ("Jacob", team);
}

// Switch chooses between integral options, with a "default" catch-all
SECTION(Switch) {
	unsigned const numTimesFooled = FIX(1);
	std::string shamee;
	switch (numTimesFooled) {
		case 0: shamee = "no one"; break;
		case 1: shamee = "you"; break;
		case 2: shamee = "me"; break;
		case 3: shamee = "my parents"; break;
		default: shamee = "evolution"; break;
	}
	EXPECT_EQ("my parents", shamee);
}

// Without a "break" or "return" statement, control "falls through" to the
//  next case...
SECTION(SwitchFallThrough) {
	unsigned const numberGrade = 4;
	char letterGrade;
	switch (numberGrade) {
		case 0: case 1: case 2: case 3: case 4: case 5: letterGrade = 'F'; break;
		case 6: letterGrade = 'D'; break;
		case 7: letterGrade = 'C'; break;
		case 8: letterGrade = 'B'; break;
		case 9:
		case 10: letterGrade = 'A'; break;
		default: letterGrade = '?'; break;
	}
	EXPECT_EQ(FIX('?'), letterGrade);
}

SECTION(For) {
	int sum = 0;
	for (int i = 0; i < FIX(6); ++i) {
		sum += i;
	}
	EXPECT_EQ(10, sum);
}

SECTION(RangeFor) {
	// Range based for loops
	int numChords;
	std::string chords[] = {"GMaj", "CMaj", "D+"};
	for (std::string const & chord: chords) {
		if (chord=="GMaj")
			numChords = 1;
		else if (chord=="CMaj")
			numChords = 2;
		else if (chord=="D+")
			numChords = 3;
		else
			numChords = 0;
	}
	EXPECT_EQ(0, numChords);
}

// for loop is useful when working with a pre-existing sequence (1 to n, first element to last, etc...)
// while loop covers most of the other cases
SECTION(While) {
	// Let's say we're reading from an io device or buffer
	int remainingReads = 15; // This is usually not exposed
	while (remainingReads > 0) {
		// Do the reading, which has this side effect...
		--remainingReads;
	}
	EXPECT_EQ(FIX(15), remainingReads);
}

// For the Book - explain for is the typical choice


// do-while loop is useful when you'll have to iterate at least once.
SECTION(DoWhile) {
	char const userInputs[] = {'y', 'y', 'n'};
	char const * inputPtr = userInputs;
	unsigned numIterations = 0;
	do {
		++numIterations;
		// Pretend we're interacting with user here... "do you want to continue?"
	}
	while (*inputPtr++ == 'y');
	EXPECT_EQ(FIX(3), numIterations);
}

double humanYearsPerDogYear(double const dogYears) {
	CREATE
	return 0;
}

SECTION(DogYears) {

}

END_CHAPTER(ControlFlow)
