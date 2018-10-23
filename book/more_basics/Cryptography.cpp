#include "luanics/crypto/Histogram.hpp"
#include "luanics/math/Operations.hpp"
#include "luanics/utility/Herald.hpp"
#include "luanics/utility/ExpressionAnalysis.hpp"

#include <cassert>
#include <random>

int main() {
	luanics::utility::Herald herald{"Crytography"};

	//*********************************************************
	// Integer division
	//*********************************************************

	int constexpr quotient = 23 / 5;
	int constexpr remainder = 23 % 5;
	static_assert(quotient == 4);
	static_assert(remainder == 3);

	auto const divResult = std::div(23, 5);
	assert(divResult.quot == 4);
	assert(divResult.rem == 3);

	//*********************************************************
	// Modular arithmetic
	//*********************************************************

	int constexpr hour = (9 + 6) % 12;
	static_assert(hour == 3);

	static_assert(23 % 5 == 3);
	static_assert(-23 % 5 == -3);

	assert(luanics::math::positiveModulo(-9, 12) == 3);

	//*********************************************************
	// Caesar cipher
	//*********************************************************


	//*********************************************************
	// Stream cipher
	//*********************************************************

	{
		char constexpr plaintext = 'b';
		char constexpr key = 'm';
		static_assert((plaintext^key)^key == plaintext);
	}

	//*********************************************************
	// Pseudo-random numbers
	//*********************************************************

	std::default_random_engine engine{};
	std::cout << "min: " << engine.min() << std::endl;
	std::cout << "max: " << engine.max() << std::endl;
	for (int i{0}; i < 2; ++i) {
		engine.seed(1);
		std::cout << "variates: ";
		for (int j{0}; j < 5; ++j) {
			std::cout << engine() << " ";
		}
		std::cout << std::endl;
	}

	for (int i{0}; i < 5; ++i) {
		std::random_device device{};
		std::cout << device() << " ";
	}
	std::cout << std::endl;

	{
		std::default_random_engine engine;

		int const min = 1;
		int const max = 9;
		std::uniform_int_distribution uniform{min, max};
		std::map<int, int> uniformFrequencies;

		double const mean = 5.5;
		double const stdDev = 3.0;
		std::normal_distribution normal{mean, stdDev};
		std::map<int, int> normalFrequencies;

		for (int i{0}; i < 10000; ++i) {
			++uniformFrequencies[uniform(engine)];
			++normalFrequencies[static_cast<int>(normal(engine))];
		}
		std::cout << "uniform" << std::endl;
		luanics::crypto::histogram(uniformFrequencies, std::cout, 20);

		std::cout << "normal" << std::endl;
		luanics::crypto::histogram(normalFrequencies, std::cout, 20);
	}

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
