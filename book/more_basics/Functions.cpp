#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>

//*********************************************************
// Overiew
//*********************************************************

void freeFunction();
class Class {
public:
	void memberFunction();
};

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

void incByValue(int param) {
	++param;
}

//*********************************************************
// Pass By Reference
//*********************************************************

void incByRef(int & param) {
	++param;
}

int multiply2(int const & x, int const & y) {
	return x * y;
}

class Integer;

int subtract(int const x, int const y);
int subtract(Integer const & x, Integer const & y);

//*********************************************************
// Input and output parameters
//*********************************************************

void zeroOut(int & param) {
	param = 0;
}

//*********************************************************
// Default arguments
//*********************************************************

int unitsDigitOf(int const x, int const base = 10) {
	return x % base;
}

//*********************************************************
// Local variables
//*********************************************************

int localMultiply(int const x, int const y) {
	int const product = x * y;
	return product;
}

//*********************************************************
// Static variables
//*********************************************************

int fibonacci() {
	static int a = 0; // ignored after first call
	static int b = 1; // ignored after first call
	int const result = b;
	b = a + b;
	a = result;
	return result;
}

std::uint32_t rnd() {
	static constexpr std::uint32_t a = 1103515245;
	static constexpr std::uint32_t c = 12345;
	static constexpr std::uint32_t m = (1u << 31) - 1u;
	static std::uint32_t seed = 1;
	seed = (a * seed + c) % m;
	return seed;
}

//*********************************************************
// Global variables
//*********************************************************

int seed = 1; // global variable
constexpr std::uint32_t a = 1103515245;
constexpr std::uint32_t c = 12345;
constexpr std::uint32_t m = (1u << 31) - 1u;
int rand() {
	seed = (a * seed + c) % m;
	return seed;
}

//*********************************************************
// Return values
//*********************************************************

//std::string & what() {
//	return std::string{"que"};
//}

std::string greet(std::string const & guest) {
	return std::string{"Hello "} + guest;
}
std::string greeting = greet("friend");

int & min(int & a, int & b) {
	return a <= b ? a : b;
}

//*********************************************************
// Trailing return type
//*********************************************************

namespace trailing_return_type {
auto multiply(int const x, int const y) -> int {
	return x * y;
}
}

namespace trailing_decltype {

//decltype(a*b) multiply(int a, int b); // ERROR - undeclared identifiers a,b

auto multiply(int a, int b) -> decltype(a*b); // OK

template <typename T>
auto subtract(T a, T b) -> decltype(a-b) {
	return a - b;
}

}

//*********************************************************
// Return type deduction
//*********************************************************

namespace return_type_deduction {

auto multiply(int a, int b) {
	return a * b;
}

template <typename T>
auto subtract(T a, T b) {
	return a - b;
}

}

//*********************************************************
// Main
//*********************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Functions"};

	//*********************************************************
	// Basics
	//*********************************************************
	int const a = multiply(2, 3); // function call
	assert(a == 6);

	//*********************************************************
	// Parameters and arguments
	//*********************************************************

	int const two = 2;
	int const six = multiply(two, 3);
	assert(six == 6);

	//*********************************************************
	// Pass by Value
	//*********************************************************

	{
		int arg = 1;
		incByValue(arg);
		assert(arg == 1); // :(
	}

	//*********************************************************
	// Pass by Reference
	//*********************************************************

	{
		int arg = 1;
		incByRef(arg);
		assert(arg == 2); // :)
	}

	int const four = 4;
	int const five = 5;
	int const twenty = multiply(four, five);
	assert(twenty == 20);

	//*********************************************************
	// Input and output parameters
	//*********************************************************

	{
		int x;
		zeroOut(x);
		assert(x == 0);
	}

	//*********************************************************
	// Default arguments
	//*********************************************************

	std::cout << "first digit of 923 base 10 = " << unitsDigitOf(923) << std::endl;
	std::cout << "first digit of 923 base 16 = " << unitsDigitOf(923,16) << std::endl;

	//*********************************************************
	// Static variables
	//*********************************************************

	assert(fibonacci() == 1);
	assert(fibonacci() == 1);
	assert(fibonacci() == 2);
	assert(fibonacci() == 3);
	assert(fibonacci() == 5);
	assert(fibonacci() == 8);
	assert(fibonacci() == 13);
	assert(fibonacci() == 21);

	//*********************************************************
	// Global variables
	//*********************************************************

	{
		seed = 0; // warning ignored :(
		int const number = rand(); // produces zero!
	}

	//*********************************************************
	// Return values
	//*********************************************************

	{
		std::cout << greet("neighbor") << std::endl;

		int x = 2;
		int y = 3;
		min(x,y) = 5;
		assert(x == 5 and y == 3);
	}

	return 0;
}
