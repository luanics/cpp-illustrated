#include "luanics/utility/Herald.hpp"
#include "luanics/utility/ExpressionAnalysis.hpp"

//*********************************************************
// Constant Expressions
//*********************************************************

constexpr int square(int const x) {return x*x;}


int main() {
	luanics::utility::Herald herald{"Expressions"};

	PRINT_ANALYSIS_OF(2);

	int x = 2;
	PRINT_ANALYSIS_OF(x);

	float const y = 2;
	PRINT_ANALYSIS_OF(y);
	PRINT_ANALYSIS_OF(std::move(y));

	struct Foo{};
	PRINT_ANALYSIS_OF(Foo{});

	//*********************************************************
	// Constant Expressions
	//*********************************************************

	constexpr int a = 42;
	static_assert(a == 42);

	static_assert(square(6) == 36);

	int beast = 666;
//	constexpr int bad = 42 + beast;   // ERROR - beast is not constexpr
	int beastSquared = square(beast); // OK - but why?
	constexpr int lucky = 7;
	constexpr int good = 42 + lucky;  // OK - lucky is constexpr
	int luckySquared = square(lucky); // OK - lucky is constexpr

	return 0;
}
