#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cfenv>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>

//*********************************************************
// comparison
//*********************************************************

bool areClose(double x, double y, double tolerance) {
	return std::abs(x - y) < tolerance;
}

bool areRelativelyClose(
	double x,
	double y,
	double relativeTolerance = 1e-6
) {
	double absoluteTolerance =
		std::max(
			std::abs(x)*relativeTolerance,
			std::abs(y)*relativeTolerance
		);
	return areClose(x, y, absoluteTolerance);
}


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

	{
		bool constexpr isIeee754 = std::numeric_limits<float>::is_iec559;
		std::cout << "is IEEE-754 supported = " << isIeee754 << std::endl;
	}

	//*********************************************************
	// Special values
	//*********************************************************

	if constexpr (std::numeric_limits<double>::has_quiet_NaN) {
		std::cout << "quiet nan supported" << '\n';
		constexpr double nan = std::numeric_limits<double>::quiet_NaN();
		double values[] = {1.0, 2.5, nan, 5.0, nan};

		double const f = nan;
		double const c = (f - 32.0) * 5.0/9.0;
		assert(std::isnan(c));
	}
	else {
		std::cout << "quiet nan not supported" << '\n';
	}

	if constexpr (std::numeric_limits<double>::has_signaling_NaN) {
		std::cout << "signaling nan supported" << std::endl;
		std::feclearexcept(FE_ALL_EXCEPT);
		constexpr double nan = std::numeric_limits<double>::signaling_NaN();
		double const f = nan;
		double const c = (f - 32.0) * 5.0/9.0;
		int code = std::fetestexcept(FE_ALL_EXCEPT);
		if (code & FE_INVALID) {
			std::cout << "FE_INVALID raised" << std::endl;
		}
	}
	else {
		std::cout << "signaling nan not supported" << std::endl;
	}

	//*********************************************************
	// Literals
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

		static_assert(0x1.0p1 == 2.0);
		static_assert(0x1.0p0 == 1.0);
		static_assert(0x1.0p-1 == 0.5);
	}

	//*********************************************************
	// IO
	//*********************************************************

	{
		std::cout << "0.1 (defaultfloat) = " << std::defaultfloat << 0.1 << '\n';
		std::cout << "0.1 (fixed)        = " << std::fixed << 0.1 << '\n';
		std::cout << "0.1 (scientific)   = " << std::scientific << 0.1 << '\n';
		std::cout << "0.1 (hexfloat)     = " << std::hexfloat << 0.1 << '\n';
	}

	{
		std::cout << "0.1 (fixed-2)      = "
			<< std::setprecision(2) << std::fixed << 0.1 << '\n';
		std::cout << "0.1 (scientific-2) = "
			<< std::setprecision(2) << std::scientific << 0.1 << '\n';
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

	if constexpr (std::numeric_limits<double>::is_iec559) {
		double const max = std::numeric_limits<double>::max();
		std::cout << " 1.0/0.0 = " << 1.0/0.0 << '\n';
		std::cout << "-1.0/0.0 = " << -1.0/0.0 << '\n';
		std::cout << " 2.0*max = " << 2.0*max << '\n';
		std::cout << "-2.0*max = " << -2.0*max << '\n';
	}

	//*********************************************************
	// comparison
	//*********************************************************

	assert(areRelativelyClose(0.1 + 0.2, 0.3));
	assert(not areRelativelyClose(0.0, 0.0));

	//*********************************************************
	// Library functions
	//*********************************************************

	assert(std::isfinite(1.0));
	assert(std::isinf(1.0/0.0));
	assert(std::isnan(0.0/0.0));;

	assert(std::ilogb(0x1.0p-1) == -1);
	assert(std::logb(0x1.0p-1) == -1.0);
	double i;
	assert(std::modf(0x1.0p-1, &i) == 0.5);
	assert(std::signbit(0x1.0p-1) == false);

	assert(std::ceil(2.1) == 3.0);
	assert(std::floor(2.9) == 2.0);
	assert(std::round(2.5) == 3.0);
	assert(std::trunc(2.5) == 2.0);

	return 0;
}


