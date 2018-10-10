#include "luanics/utility/Herald.hpp"

#include <cassert>

//*********************************************************
// void
//*********************************************************

void exercise(void) { // nothing in, nothing out
}

//*********************************************************
// Function types
//*********************************************************

float speed(float distance, float time) {
	return distance / time;
}

//std::string caloriesBurned(int numLaps) {
//	return 1; // ERROR - can't convert int to string
//}

//*********************************************************
// Enumerations
//*********************************************************

int main() {
	luanics::utility::Herald herald{"Types"};

	//*********************************************************
	// Static but weak
	//*********************************************************

	float heartRate = 120.6;
	int rate = heartRate;                    // implicit conversion
	int pulse = static_cast<int>(heartRate); // explicit conversion

	//*********************************************************
	// Arithmetic types
	//*********************************************************

	bool isWorkoutFinished = false;

	char const factor = '+';

	unsigned int numPushUps = 5;
	int changeInWeight = -10;

	float caloriesPerHour = 427.3;

	//*********************************************************
	// Array types
	//*********************************************************

	int calories[5] = {30,200,120,550,145};
	assert(calories[0] == 30);
	calories[4] = 560;
	assert(calories[4] == 560);

	//*********************************************************
	// Closure types
	//*********************************************************

	auto speed = [](float distance, float time){return distance / time;};
	assert(speed(200.0,4.0) == 50.0);

	//*********************************************************
	// Enumerations
	//*********************************************************

	class Stuff {};
	enum Medal {GOLD = 1, SILVER, BRONZE};
	std::cout << "gold = " << GOLD << std::endl;


	return 0;
}
