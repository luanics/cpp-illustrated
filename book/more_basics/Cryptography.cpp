#include "luanics/crypto/Histogram.hpp"
#include "luanics/utility/Herald.hpp"
#include "luanics/utility/ExpressionAnalysis.hpp"

#include <cassert>
#include <random>

int main() {
	luanics::utility::Herald herald{"Crytography"};

	//*********************************************************
	// Integer division
	//*********************************************************

	auto constexpr quotient = 23 / 5;
	auto constexpr remainder = 23 % 5;
	static_assert(quotient == 4);
	static_assert(remainder == 3);

	auto const divResult = std::div(23, 5);
	assert(divResult.quot == 4);
	assert(divResult.rem == 3);

	//*********************************************************
	// Modular arithmetic
	//*********************************************************

	auto constexpr hour = (9 + 6) % 12;
	static_assert(hour == 3);

	//*********************************************************
	// Pseudo-random numbers
	//*********************************************************

	std::random_device device;

	std::map<int, int> frequencies{
		{1, 3},
		{2, 4},
		{3, 5},
		{4, 4},
		{5, 3}
	};
	luanics::crypto::histogram(frequencies, std::cout);

	return 0;
}
