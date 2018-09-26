#include "luanics/testing/Tutorial.hpp" // This imports some code that we wrote

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <type_traits> // This imports some code that is part of the standard C++ library
#include <unordered_map>

using namespace luanics;
using namespace std;

BEGIN_CHAPTER(Statements)

// * Statements are commands for the computer.
// * C++ programs are composed of a sequence of statements.
// * Statements are executed (no value), expressions are evaluated (value).
// * Most, but not all, statements end with a semicolon.
// * All whitespace is treated equally, and consecutive whitespaces are effectively collapsed.
// * There are roughly five categories of statement:
//   * expression statement is an expression followed by a semicolon
//   * declaration statement introduces a name and associates it with an entity
//   * compound statement is a group of statements in curly braces
//   * control flow statements redirect the flow of execution, e.g., for-statement and if-statement
//   * try-block statement is used for exception handling
// * The one-definition rule (ODR) says that an entity may have multiple declarations, but only one definition per translation unit.
// * Don't confuse initialization (using '='), assignment (using '='), and equality comparison (using '==').

SECTION(DeclarationStatements) {
	// Here we define and initialize two variables.
	// Fix the initialization to pass the test.
	int numBlows = FIX(3);
	int damagePerBlow = FIX(5);
	int const totalDamage = numBlows * damagePerBlow;
	EXPECT_EQ(14, totalDamage);
}

SECTION(OneDefinitionRule) {
	// To see ODR in action, uncomment the following line
	//#define IS_ACTIVE
	#ifdef IS_ACTIVE
		int unicorn;
		int unicorn;
	#endif
	#undef IS_ACTIVE
	EXPECT_REACHED();
}

int goodRoll() {return 20;}
int badRoll() {return 1;}

SECTION(ExpressionStatements) {
	int roll = 6; // definition statement with initialization - not assignment.
	roll = FIX(5); // assignment statement
	EXPECT_EQ(roll, 2);

	// Another useful expression is the function call
	roll = FIX(badRoll()); // assignment and function call
	EXPECT_EQ(roll, 20);

	// Don't confuse assignment (=) with equality comparison (==)
	if (roll FIX(=) 1) {
		EXPECT_NOT_REACHED();
	}
	roll FIX(==) 19;
	EXPECT_EQ(19, roll);
}

SECTION(SelectionStatements) {
	// The simplest selection statement is the "if statement".

	// Here we give a bonus if a condition is met:
	int reward = 100;
	bool isDungeonClean = true;
	if (isDungeonClean)
		reward = reward + 10;
	EXPECT_EQ(FIX(100), reward);

	// Kickin' it up a notch, the if-else statement selects one of two options.
	reward = 100;
	isDungeonClean = false;
	if (isDungeonClean)
		reward = reward + 10;
	else
		CREATE ;
	EXPECT_EQ(90, reward);
}

SECTION(IterationStatements) {
	// The workhorse of iteration statements is the "for loop".
	int baseRoll = 15;
	int modifiedRoll = baseRoll;
	std::vector<int> rollModifiers{+1, -2, +3};
	for (int i = 0; i < 3; ++i)
		modifiedRoll += rollModifiers[i];
	EXPECT_EQ(FIX(15), modifiedRoll)

	std::string name;
	for (char ch = 'a'; ch <= 'e'; ch = ch + FIX(1))
		name += ch;
	EXPECT_EQ("ace", name);
}

SECTION(CompoundStatements) {
	// if statements can make use of compound statements
	int reputation = 1000;
	int gold = 100;
	if (true) {
		CREATE
	}
	EXPECT_EQ(reputation, 900);
	EXPECT_EQ(gold, 110);
}

SECTION(TryBlockStatements) {
	// try-blocks are used for exception handling
	bool isEverythingOk= true;
	try {
		std::string thoughts = "Hum, dee, hum, dee, hum...";
		throw std::runtime_error("Oh, No!!!");
	}
	catch (...) {
		CREATE
	}
	EXPECT_FALSE(isEverythingOk);
}

SECTION(BewareDopplegangers) {
	// Change (add or remove) one character in the following code to make it pass.
	int numPuzzlesSolved{0};
	if (numPuzzlesSolved = 0) {
		++numPuzzlesSolved;
	}
	EXPECT_EQ(1, numPuzzlesSolved);
}

END_CHAPTER(Statements)
