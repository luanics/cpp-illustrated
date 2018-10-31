#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cfenv>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <type_traits>

//#pragma STDC FENV_ACCESS ON

int main(int argc, char ** argv) {
	luanics::utility::Herald herald("ArithmeticTypes");

	//*********************************************************
	// Literals
	//*********************************************************

	unsigned char const decimal = 142;
	unsigned char const binary = 0b10001110;
	assert(binary == decimal);
	unsigned char const octal = 0216;
	assert(octal == decimal);
	unsigned char const hex = 0x8E;
	assert(hex == decimal);

	//*********************************************************
	// Bases
	//*********************************************************

	auto const oneMillion = 1'000'000;
	auto const oneMega = 0b1'0000000000'0000000000;
	std::cout << "oneMillion=" << oneMillion << std::endl;
	std::cout << "oneMega=" << oneMega << std::endl;
	std::cout << "oneMillion = " << std::hex << oneMillion << std::endl;
	std::cout << "oneMega    = " << std::hex << oneMega << std::endl;
	std::cout << "oneMillion = " << std::hex << std::uppercase << oneMillion << std::endl;
	std::cout << "oneMega    = " << std::hex << std::uppercase << oneMega << std::endl;
	std::cout << std::dec;

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

	bool b1{0};
	assert(b1 == false);
	bool b2{1};
	assert(b2 == true);
	bool b3 = 7;
	assert(b3 == true);

	assert(sizeof(bool) == 1);

	//*******************************************************************
	// char
	//*******************************************************************

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
	// Size and Sign
	//*******************************************************************

	std::cout << "sizeof(short int) = " << sizeof(short int) << std::endl;
	std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
	std::cout << "sizeof(long int) = " << sizeof(long int) << std::endl;
	std::cout << "sizeof(long long int) = " << sizeof(long long int) << std::endl;

	assert(sizeof(char) == 1);
	assert(sizeof(unsigned char) == 1);
	assert(sizeof(signed char) == 1);

	//*******************************************************************
	// Integral Aliases
	//*******************************************************************

//	std::cout << "std::uint_least8_t= " << std::numeric_limits<std::uint_least8_t>::max() << std::endl;
//	std::cout << "UINT_LEAST16 = " << UINT_LEAST16_MAX << std::endl;
//	std::cout << "UINT_LEAST32 = " << UINT_LEAST32_MAX << std::endl;
//	std::cout << "UINT_LEAST64 = " << UINT_LEAST64_MAX << std::endl;

	//*******************************************************************
	// Integral Pitfalls
	//*******************************************************************

	uint8_t big = 252;
	big += 7;
//	assert(big == 259); // ERROR - forgot overflow
	assert(big == 3); // OK - overflow

	int_least16_t bigger = 32765;
	std::cout << "bigger = " << bigger << std::endl;
	bigger +=3;

	std::cout << "bigger = " << bigger << std::endl;
	bigger -= 5;
	std::cout << "bigger = " << bigger << std::endl;
//	bigger -= 5;
//	std::cout << "bigger = " << bigger << std::endl;
//	bigger /= 5;
//	std::cout << "bigger = " << bigger << std::endl;

	{
		std::array<int, 5> numbers{1, 2, 3, 4, 5};
		std::size_t index = 2;
		std::size_t offset = 3;
		index -= offset;
		std::cout << numbers[index] << std::endl;
//		std::cout << numbers.at(index) << std::endl; // ERROR - out of range
	}

	int big1 = 1'200'000'000;
	int big2 = 1'500'000'000;
	int big3 = 1'0'000'000;
	int meanBig = (big1 + big2 + big3) / 3; // UB
//	assert(meanBig == 1'500'000'000); // FAIL

	//*******************************************************************
	// Floating Point
	//*******************************************************************

	std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
	std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
	std::cout << "sizeof(long double) = " << sizeof(long double) << std::endl;



	float bigNum = 1.8e7;
	float smallNum = 1.;
	float sumWithBig = bigNum;
	std::feclearexcept(FE_ALL_EXCEPT);
	for (size_t i = 1; i < 1000; ++i) {
		sumWithBig += smallNum;
	}
	if (std::fetestexcept(FE_INEXACT)) {
		std::cout << "inexact result reported" << std::endl;
	} else {
		std::cout << "inexact result not reported" << std::endl;
	}
	// assert(sumWithBig > bigNum); // error -- sumWithBig == bigNum

	float sum=0;
	for (size_t i=1; i < 1000; ++i) {
		sum += smallNum;
	}
	sumWithBig = bigNum + sum;
	assert(sumWithBig > bigNum);

	float numerator = 1.0;
	float denominator = 0.0;
	std::feclearexcept(FE_ALL_EXCEPT);
	float result = numerator / denominator;
	std::cout << "1.0/0.0 = " << result << std::endl;
	if (std::fetestexcept(FE_DIVBYZERO)) {
		std::cout << "divide by zero reported" << std::endl;
	} else {
		std::cout << "divide by zero not reported" << std::endl;
	}

	if (std::isinf(result)) {
		std::cout << "result is inf" << std::endl;
	} else {
		std::cout << "result is not inf" << std::endl;
	}
	std::feclearexcept(FE_ALL_EXCEPT);
	std::cout << "1.0/result = " << numerator/result << std::endl;

	std::cout << "isnan{0.0 / 0.0}" <<
			std::isnan(0.0 / 0.0) << std::endl;
	std::cout << "isnan(Inf - Inf)" <<
			std::isnan(INFINITY - INFINITY) << std::endl;
	//*******************************************************************
	// Integer Literals
	//*******************************************************************
	short int x1 = 19149;
	int16_t x2 = 045315;
	int16_t x3 = 0x4ACD;
	uint8_t x4 = 145u;
	uint8_t x5 = 0b10010001u;
	assert(x1==x2);
	assert(x2==x3);
	assert(x4==x5);
//	uint16_t baux = 23;
//	uint16_t maux = 8;
//	uint16_t mb = maux - baux;
//	std::cout << "mb = " << mb << std::endl;


	//*********************************************************
	// implementation
	//*********************************************************

	std::cout << "is IEEE-754 supported = " << std::numeric_limits<float>::is_iec559 << std::endl;

	//*********************************************************
	// inexact representation
	//*********************************************************
	{
		int const number = 987'654'321;
		float const numberAsFloat = number;
		int const numberAsIntAgain = numberAsFloat;
		static_assert(number != numberAsIntAgain);
		std::cout << "numberAsIntAgain=" << numberAsIntAgain << std::endl;
		static_assert(static_cast<int>(static_cast<float>(987'654'321)) != 987'654'321);

		static_assert(0.1 + 0.2 != 0.3);
		std::cout << std::hexfloat << "0.1       = " << 0.1 << std::endl;
		std::cout << std::hexfloat << "0.2       = " << 0.2 << std::endl;
		std::cout << std::hexfloat << "0.1 + 0.2 = " << 0.1 + 0.2 << std::endl;
		std::cout << std::hexfloat << "0.3       = " << 0.3 << std::endl;

		static_assert(0.5 + 0.5 == 1.0);
		std::cout << std::hexfloat << "0.5       = " << 0.5 << std::endl;
		std::cout << std::hexfloat << "1.0       = " << 1.0 << std::endl;
	}

	//*********************************************************
	// overflow and divide by zero
	//*********************************************************

	using FloatTraits = std::numeric_limits<float>;
	bool const isIeee754Supported = FloatTraits::is_iec559;
	if (isIeee754Supported) {
		assert(FloatTraits::has_infinity);
		assert(FloatTraits::has_quiet_NaN);
		assert(FloatTraits::has_signaling_NaN);

		assert(1.0f/0.0f == FloatTraits::infinity());
		assert(0.0f/0.0f == FloatTraits::signaling_NaN());
	}

	return 0;
}
