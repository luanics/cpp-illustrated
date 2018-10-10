#include "luanics/utility/Herald.hpp"

#include <iostream>
#include <vector>

struct Dice {
	int roll() {return 7;}
};

struct ImpossibleDiceRoll {};

struct Hero {
	void expire() {};
};

struct Game {
	void end() {};
};

void replaceDice() {}

int main() {
	luanics::utility::Herald herald{"Statements"};

	//*********************************************************
	// Expression Statements
	//*********************************************************

	int health, vitality;
	health = 9;
	vitality = (health = 2 + 2);  	// OK - "health=2+2" is an expression
//	vitality = (health = 2 + 2;); // ERROR - "health=2+2;" is a statement

	int wisdom = 12;    // "=" is initialization since wisdom is being defined
	wisdom = 13;       // "=" is assignment since wisdom already defined
	if (wisdom == 18) { // "==" is comparison
		std::cout << "sage" << std::endl;
	}

	//*********************************************************
	// Declaration Statements
	//*********************************************************

	int gold;          // Declare a variable named "gold" of type "int"
	class Unknown {};  // Declare a class named "Unknown"
	Hero cassie;       // Declare a variable named "cassie" of type "Hero"
	extern int level;  // Declare a variable named "level" of type "int"
	class Monster;     // Declare a class named "Monster"
	int score();       // Declare a function named "score" that returns int

	//*********************************************************
	// Variable Declarations
	//*********************************************************

	int reputation;          // Variable definition with no initializer
	float multiplier = 1.45; // Variable definition with "=" initializer
	extern int roll;         // Variable pure-declaration

	//*********************************************************
	// Compound Statement
	//*********************************************************

	bool isAttacked = true;
	Hero adventurer;
	Game game;

	if (isAttacked)
		health -= 5;         // statement
	if (health <= 0)
	{                        // com
		adventurer.expire(); //    pound
		game.end();          //          state
	}                        //               ment

	//*********************************************************
	// Control Flow Statements
	//*********************************************************

	bool isQuestSuccessful = false;
	if (isQuestSuccessful) {
		gold += 100;
		reputation += 1000;
	}
	else {
		reputation -= 1000;
	}

	std::vector<std::string> languages = {"Elvish", "Dwarvish", "Common"};
	for (size_t i = 0; i < 3; ++i) {
		std::cout << "Do you speak " << languages[i] << "?" << std::endl;
	}

	//*********************************************************
	// try-block
	//*********************************************************

	Dice dice;

	try {
		int roll = dice.roll();
		if (roll <= 0) {
			throw ImpossibleDiceRoll{};
		};
	}
	catch (...) {
		replaceDice();
	}

	return 0;
}
