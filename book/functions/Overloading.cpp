#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

//*******************************************************************
// Basics
//*******************************************************************

int absolute(int x) {
	return std::abs(x);
}

double absolute(double x) {
	return std::fabs(x);
}

//*********************************************************
// Example
//*********************************************************

//void print(bool const value) {std::cout << value << std::endl;}
void print(char const value) {std::cout << value << std::endl;}
//void print(uint8_t const value) {std::cout << value << std::endl;}
//void print(int8_t const value) {std::cout << value << std::endl;}
void print(uint16_t const value) {std::cout << value << std::endl;}
void print(int16_t const value) {std::cout << value << std::endl;}

void print(bool const value) {
	std::cout << std::boolalpha << value << std::endl;
}
void print(uint8_t const value) {
	std::cout << static_cast<uint16_t>(value) << std::endl;
}
void print(int8_t const value) {
	std::cout << static_cast<int16_t>(value) << std::endl;
}


//*******************************************************************
// Lookup
//*******************************************************************

namespace math {
	struct Number {int value;};
	Number multiply(Number lhs, Number rhs) {
		return Number{lhs.value * rhs.value};
	}
	Number multiply(Number lhs, int rhs) {
		return Number{lhs.value * rhs};
	}
}
int multiply(int a, int b, int c) {return a*b*c;}
double multiply(double a, double b) {return a * b;}

//*******************************************************************
// Lookup
//*******************************************************************

auto const multiplied = multiply(math::Number{2}, 3.0);


// Regular lookup for overload set follows standard rules...
// ... once matches are found in a scope, search stops
namespace F1 {
	void f(int) {std::cout << "f(int)" << std::endl;}
	namespace F2 {
		void f(double) {std::cout << "f(double)" << std::endl;}
		void g() {f(2);}
	}
}

//*********************************************************
// Function Name Lookup
//*********************************************************

namespace M {
	namespace N {
		struct Number {int value;};
		void f(Number & n, int i) {
			n.value += i;
		}
	}
	//void f(N::Number) {
	//	std::cout << "N::f" << std::endl;
	//}
}

namespace O {
	void f(M::N::Number & n, double d) {
		n.value *= static_cast<int>(d);
	}
	namespace P {
		void g() {
			M::N::Number number{1};
			f(number, 1);
		}
	}
}

//*********************************************************
// Main
//*********************************************************

int main(int argc, char ** argv) {
	luanics::Herald herald{"Overloading"};

	//*******************************************************************
	// Basics
	//*******************************************************************
	auto const x = absolute(-10);   // invokes absolute(int)
	auto const y = absolute(-10.0); // invokes absolute(double)

	//*******************************************************************
	// Example
	//*******************************************************************
	bool const one = true;
	char const two = 'a';
	uint8_t const three = 97;
	int8_t const four = 97;
	uint16_t const five = 97;
	int16_t const six = 97;
	print(one);
	print(two);
	print(three);
	print(four);
	print(five);
	print(six);



//	Int const one{1};
//	Int const two{2};
//	Int const three{3};
////	Int const a = operator+(1, two);
//	Int const onePlusTwo = one + two;
//	Int const plusOneTwo = operator+(one, two);
//	assert(onePlusTwo == three);
//	assert(plusOneTwo == three);
////	int const b = operator+()(1,1);

	return 0;
}
