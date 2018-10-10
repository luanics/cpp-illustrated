#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>

//*********************************************************
// Basics
//*********************************************************

int add(int const x, int const y);       // pure declaration
int multiply(int const x, int const y) { // definition
	return x * y;
}

//*********************************************************
// Pass by Value
//*********************************************************

void inc1(int param) {
	++param;
}

//*********************************************************
// Pass By Reference
//*********************************************************

void inc2(int & param) {
	++param;
}

void inc3(int && param) {
	++param;
}

//*********************************************************
// Pass by Const Reference
//*********************************************************

int multiply2(int const & x, int const & y) {
	return x * y;
}

int subtract(int const x, int const y);
class Integer;
int subtract(Integer const & x, Integer const & y);

//*********************************************************
// Default Arguments
//*********************************************************

int multiply3(int const x, int const y, int const base = 10) {
	return (x * y) % base;
}

//*********************************************************
// Static variables
//*********************************************************

uint32_t rnd() {
	static constexpr uint32_t a = 1103515245;
	static constexpr uint32_t c = 12345;
	static constexpr uint32_t m = (1u << 31) - 1u;
	static uint32_t seed = 1;
	seed = (a * seed + c) % m;
	return seed;
}

//*********************************************************
// Main
//*********************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Lambdas"};
	//*********************************************************
	// Parameters and Arguments
	//*********************************************************

	int const two = 2;
	int const six = multiply(two, 3);
	assert(6 == six);

	//*********************************************************
	// Pass by Value
	//*********************************************************

	int arg1 = 1;
	inc1(arg1);
	assert(arg1 == 1); // :(

	//*********************************************************
	// Pass by Reference
	//*********************************************************

	int arg2 = 1;
	inc2(arg2);
	assert(arg2 == 2); // :)

	int arg3 = 1;
	inc3(std::move(arg3));
	assert(arg3 == 2); // ?

	//*********************************************************
	// Pass by Const Reference
	//*********************************************************

	int const four = 4;
	int const five = 5;
	int const twenty = multiply(four, five);
	assert(twenty == 20);
	int const whatever = multiply3(four, five, 10);
	std::cout<< "whatever = " << whatever << std::endl;

	return 0;
}
