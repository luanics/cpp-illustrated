#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cfenv>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <type_traits>

int main(int argc, char ** argv) {
	luanics::utility::Herald herald("IntegralTypes");

	//*********************************************************
	// Bases
	//*********************************************************

	unsigned char const decimal = 142;
	unsigned char const binary = 0b10001110;
	assert(binary == decimal);
	unsigned char const octal = 0216;
	assert(octal == decimal);
	unsigned char const hex = 0x8E;
	assert(hex == decimal);

//	auto const oneMillion = 1,000,000; // ERROR
	auto const oneMillion = 1'000'000; // OK
	auto const oneMega = 0b1'0000000000'0000000000;
	std::cout << "oneMillion=" << oneMillion << std::endl;
	std::cout << "oneMega=" << oneMega << std::endl;

	std::cout << "oneMillion = " << std::hex << oneMillion << std::endl;
	std::cout << "oneMega    = " << std::hex << oneMega << std::endl;
	std::cout << "oneMillion = " << std::hex << std::uppercase << oneMillion << std::endl;
	std::cout << "oneMega    = " << std::hex << std::uppercase << oneMega << std::endl;
	std::cout << std::dec; // Restore to decimal

	//*******************************************************************
	// sizeof operator
	//*******************************************************************

	assert(sizeof(char) == 1);   // sizeof type
	char number = 123;
	assert(sizeof(number) == 1); // sizeof expression

	//*******************************************************************
	// bool
	//*******************************************************************
	int x = 7;
	int y = 3;
	bool z{x > y};
	std::cout << "z = " << z << " (" << std::boolalpha << z << ")" << std::endl;

	assert(sizeof(bool) == 1);

	//*******************************************************************
	// char
	//*******************************************************************

	assert(sizeof(char) == 1);
	assert(sizeof(unsigned char) == 1);
	assert(sizeof(signed char) == 1);

	char const a{97};
	assert(a == 'a');
	char const b = a + 1;
	assert(b == 'b');
	std::cout << "a = " << a << std::endl;
	std::cout << "a + 1 = " << a + 1 << std::endl;
	std::cout << "b = " << b << std::endl;

	char c = 'c';
	std::cout << "c = " << static_cast<int>(c) << std::endl;

	//*******************************************************************
	// integral aliases
	//*******************************************************************

	short int x1 = 19149;
	std::int16_t x2 = 045315;
	std::int16_t x3 = 0x4ACD;
	assert(x1==x2);
	assert(x2==x3);
	std::uint8_t x4 = 145u;
	std::uint8_t x5 = 0b10010001u;
	assert(x4==x5);

	//*******************************************************************
	// Integral Pitfalls
	//*******************************************************************

	{
		std::uint8_t big = 252;
		big += 7;
//		assert(big == 259); // ERROR - forgot overflow
		assert(big == 3); // OK - overflow
	}

	{
		std::int8_t x = 127;
		x += 7; // UB - signed overflow
	}

	{
		int big1 = 1'200'000'000;
		int big2 = 1'500'000'000;
		int big3 = 1'800'000'000;
		int meanBig = (big1 + big2 + big3) / 3; // UB
//		assert(meanBig == 1'500'000'000); // FAIL
	}

	{
		int a = -1;
		unsigned b = 0;
//		assert(a + b < 0); // FAIL
		assert(a + b > 0);
	}

	{
		int sum = 0;
		int count = 0;
		// Add up some numbers... maybe
		int mean = sum /count; // UB if count == 0
	}

	//*******************************************************************
	// Floating Point
	//*******************************************************************

	std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
	std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
	std::cout << "sizeof(long double) = " << sizeof(long double) << std::endl;

	return 0;
}
