#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <complex>
#include <cstdint>
#include <ios>
#include <iostream>
#include <type_traits>

//*********************************************************
// Special operators
//*********************************************************

int doubled(int x) {return 2 * x;}

int & max(int & a, int & b) {
	return a < b ? b : a;
}

struct Doubler {
	int operator()(int x) const {return 2*x;}
};

constexpr int16_t WORK_HOURS_PER_DAY = 8;

struct Coder {
	void discipline() {breaksPerDay -= 1;}
	void train() {linesPerHour += 10;}
	int16_t linesPerDay() {
		return linesPerHour * (WORK_HOURS_PER_DAY - breaksPerDay);
	}

	std::string name;
	uint32_t serialNumber;
	int16_t linesPerHour;
	int8_t breaksPerDay;
};

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Operators"};

	//*********************************************************
	// Basics
	//*********************************************************

	{
		std::complex<double> ac = 1.0;
		std::complex<double> bc = 2.0;
		std::complex<double> cc = ac + bc; // OK
		std::complex<double> dc = operator+(ac, bc); // OK
		assert(cc == dc);

		int ai = 1;
		int bi = 2;
		int ci = ai + bi; // OK
	//	int di = operator+(ai, bi); ERROR
		assert(ci == 3);
	}

	//*********************************************************
	// Precedence
	//*********************************************************

	{
		int const x = 2;
		int const y = 1;
		int const z = 3*x - 2*y;
		assert(z == 4);
		int const zParens = ( ( (3) * (x) ) - ( (2) * (y) ) );
		assert(zParens == 4);
	}

	//*********************************************************
	// Associativity
	//*********************************************************

	{
		int const z1 = 2 / 1 * 3; // (2 / 1) * 3
		assert(z1 == 6);
	}

	//*********************************************************
	// Conversion
	//*********************************************************

	{
		auto a = 1 + 1.0; // int converted to float
		static_assert(std::is_same_v<decltype(a), double>);

		static_assert(std::is_same_v<std::common_type_t<double, float>, double>);
		static_assert(std::is_same_v<std::common_type_t<float, unsigned>, float>);
		static_assert(std::is_same_v<std::common_type_t<unsigned, int>, unsigned>);
	}

	//*********************************************************
	// Logical operators
	//*********************************************************

	{
		bool b1{false};
		bool b2{true};

		assert((b1 && b2) == false);
		assert((b1 || b2) == true);
		assert(!b1 == b2);

		assert((b1 and b2) == false);
		assert((b1 or b2) == true);
		assert((not b1) == b2);

		std::string sentence{};
		[[maybe_unused]] bool const isFinished = sentence.empty() or sentence.back() == '.';

		static_assert((not 0) and 2);
	}

	//*******************************************************************
	// Bitwise Logical and shift operators
	//*******************************************************************

	{
		uint8_t const x = 0b11110000;
		uint8_t const y = 0b10101010;
		uint8_t const z = x & y;
		assert(z == 0b10100000);
		uint8_t xs = x << 2;
		assert(xs == 0b11000000);
	}

	//*******************************************************************
	// Comparison operators
	//*******************************************************************

	{
		int a = 1;
		int b = 2;
		int c = 3;
		assert(a < b < c);  	// OK
		assert(b < a < c);   // Also OK!
	}

	//*******************************************************************
	// Arithmetic operators
	//*******************************************************************

	{
		assert(6 % 3 == 0);
		assert(7 % 3 == 1);
		assert(8 % 3 == 2);
		assert(9 % 3 == 0);
	}

	//*******************************************************************
	// Increment and decrement operators
	//*******************************************************************

	{
		int j = 1;
		int k = ++j;
		assert(j==2);
		assert(k==2);
		int l = --j;
		assert(j==1);
		assert(l==1);
	}

	{
		int j = 1;
		int k = j++;
		assert(j==2);
		assert(k==1);
		int l = j--;
		assert(j==1);
		assert(l==2);
	}

	for (int i = 0; i < 5; ++i) {
		std::cout << i << std::endl;
	}

	for (int i = 0; i < 5; i++) {
		std::cout << i << std::endl;
	}

	//*********************************************************
	// Assignment operators
	//*********************************************************

	{
		int t = 7;
		int u = t += 7;
		assert(t==14);
		assert(u==14);
	}

	//*********************************************************
	// Special operators
	//*********************************************************

	{
		int val = 23;
		int * ptr = &val; // address of operator
		assert(*ptr == 23); // dereference operator
	}

	{
		auto fp = &doubled;
		int y = (*doubled)(2);
		assert(y == 4);
	}

	{
		int data[] = {4, 5, 6};
		assert(data[0] == 4);
	}

	{
		int a = 1;
		int b = 2;
		++max(a, b);
		assert(a == 1);
		assert(b == 3);
	}

	{
		double a = 1.0;
		int b = 1;
		auto c = true ? a : b;
//		auto d = true ? a : "b";
		static_assert(std::is_same_v<std::common_type_t<decltype(a), decltype(b)>, decltype(c)>);
		static_assert(std::is_same_v<double, decltype(c)>);
	}

	{
		Doubler d;
		assert(d(2) == 4);
	}

	{
		Coder john{"John", 10101, 100, 2};
		Coder * peterson = &john;
		assert(john.name == "John"); // member of object operator
		assert(peterson->name == "John"); // member of pointer operator

		assert(john.linesPerHour == 100);
		void (Coder::* memberPtr)(void) = &Coder::train;
		(john.*memberPtr)(); // Call train() through pointer to member of object
		assert(john.linesPerHour == 110);
		memberPtr = &Coder::discipline;
		(john.*memberPtr)(); // Call discipline() through pointer to member of object
		assert(john.breaksPerDay == 1);

		(peterson->*memberPtr)(); // Call disclipline() through pointer to member of pointer
		assert(john.breaksPerDay == 0);
	}

	return 0;
}
