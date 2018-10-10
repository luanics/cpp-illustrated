#include <iostream>
#include <type_traits>

//*********************************************************
// Templates
//*********************************************************

template <typename T>
void f(T &) {}

int main(int argc, char ** argv) {

	//*********************************************************
	// Overview
	//*********************************************************

	auto number = 1;


	//*********************************************************
	// Review
	//*********************************************************

	int x = 1;
	int const & y = 2;
	int * const z = &x;

	static_assert(
		std::is_same<int, decltype(x)>::value,
		"x is an int"
	);
	static_assert(
		std::is_same<int const &, decltype(y)>::value,
		"y is an int const &"
	);
	static_assert(
		std::is_same<int * const, decltype(z)>::value,
		"z is an int * const"
	);
	static_assert(
		std::is_same<int &, decltype((x))>::value,
		"(x) is an int lvalue expression"
	);
	static_assert(
		std::is_same<int const &, decltype((y))>::value,
		"(y) is an int const lvalue expression"
	);
	static_assert(
		std::is_same<int * const &, decltype((z))>::value,
		"(z) is an int * const lvalue expression"
	);
	static_assert(
		std::is_same<int, decltype((x+y))>::value,
		"(x + y) is an int rvalue expression"
	);

	//*********************************************************
	// Basics
	//*********************************************************

	{
		int numCookies = 10;
		static_assert(std::is_same_v<int, decltype(numCookies)>);

	}
	{
		auto numCookies = 9; // auto -> int
		static_assert(std::is_same_v<int, decltype(numCookies)>);
	}
//	extern auto x; // auto -> ?
//	auto x;        // auto -> ?
//	auto x{};      // auto -> ?

	//*********************************************************
	// Terminology
	//*********************************************************

	{
		auto numCookies = 8; // auto -> int
		static_assert(std::is_same_v<int, decltype(numCookies)>);
	}

	//*********************************************************
	// Adornments
	//*********************************************************

	{
		int left = 7;
		auto const & numCookies = left;
	}
	int remaining = 6;
	{
		auto numCookies = remaining; // auto -> int
		static_assert(std::is_same_v<int, decltype(numCookies)>);
	}
	--remaining;
	{
		auto & numCookies = remaining; // auto -> int
		static_assert(std::is_same_v<int &, decltype(numCookies)>);
	}
	{
		int const uneaten = 4;
		auto numCookies = uneaten; // auto -> int
		static_assert(std::is_same_v<int, decltype(numCookies)>);
	}
	{
		int const untouched = 3;
		auto & numCookies = untouched; // auto -> int const
		static_assert(std::is_same_v<int const &, decltype(numCookies)>);
	}

	//*********************************************************
	// Forwarding references
	//*********************************************************

	{
		auto && numCookies = 2;
	}
	{
		int const alone = 1;
		auto && numCookies = alone;
		static_assert(std::is_same_v<int const &, decltype(numCookies)>);
	}
	{
		auto && numCookies = 0;
		static_assert(std::is_same_v<int &&, decltype(numCookies)>);
	}

	//*********************************************************
	// decltype(auto)
	//*********************************************************

	decltype(auto) numFingerprints = 2; // decltype(auto) -> int
	static_assert(std::is_same_v<int, decltype(numFingerprints)>);
	decltype(auto) numSuspects = numFingerprints; // decltype(auto) -> int
	static_assert(std::is_same_v<int, decltype(numSuspects)>);
	decltype(auto) numSmudges = (numFingerprints); // decltype(auto) -> int &
	static_assert(std::is_same_v<int &, decltype(numSmudges)>);

	//*********************************************************
	// Initialization forms
	//*********************************************************

	auto a{1};      // auto -> std::initializer_list<int>
	auto b = {2.0}; // auto -> std::initializer_list<float>
	auto c(1);      // auto -> int
	auto d = 1;     // auto -> int

	//*********************************************************
	// Templates
	//*********************************************************

	int u;
	f(u); // FuncParam->int &, TemplParamT->int
//	f(2); // ERROR - cannot bind non-const lvalue ref to rvalue
	int const & v = u;
	f(v); // FuncParam->int const &, TemplParamT->int const

	return 0;
}
