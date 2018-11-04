#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <type_traits>

int main(int argc, char ** argv) {
	luanics::utility::Herald herald("FloatingPointTypes");

	//*********************************************************
	// Overview
	//*********************************************************

	double constexpr plancksConstant = 6.62e-34;
	double constexpr avogadroConstant = 6.02e23;

	//*********************************************************
	// Binary floating point
	//*********************************************************

	bool constexpr isIeee754 = std::numeric_limits<float>::is_iec559;
	std::cout << "is IEEE-754 supported = " << isIeee754 << std::endl;

	//*********************************************************
	// floating-point literals
	//*********************************************************

	{
		auto const a = 3.0;    // OK - double literal
		auto const b = .27;    // OK - double literal
		auto const c = 9.283;  // OK - double literal
		auto const d = 2e10;   // OK - double literal
		auto const e = .28E-6; // OK - double literal
//		auto const f = 3e 10   // ERROR - no spaces allowed
		auto const g = 4.l;    // OK - long double literal
		auto const h = 5l;     // OK - long int literal
		auto const i = 6.f;    // OK - float literal
//		auto const j = 7f;     // ERROR - float suffix with integer literal
	}

	//*********************************************************
	// inexact representation
	//*********************************************************
	{
		int const numberAsInt = 987'654'321;
		std::cout << "numberAsInt      = " << numberAsInt << std::endl;
		float const numberAsFloat = numberAsInt;
		int const numberAsIntAgain = numberAsFloat;
		static_assert(numberAsInt != numberAsIntAgain);
		std::cout << "numberAsIntAgain = " << numberAsIntAgain << std::endl;
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


