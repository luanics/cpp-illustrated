#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>
#include <optional>

int main() {
	luanics::Herald herald{"Errors"};

	struct WildBall {};
	bool isCaught = false;
	try {
		throw WildBall{};
	}
	catch (WildBall const &) {
		isCaught = true;
	}
	assert(isCaught);

	//*********************************************************
	// Error communication
	//*********************************************************

	std::optional<int> maybeNumber;
	assert(not maybeNumber);
	assert(not maybeNumber.has_value());
	try {
		std::cout << maybeNumber.value() << std::endl; // will throw
	}
	catch (std::bad_optional_access const & error) {}
	maybeNumber = 10;
	assert(maybeNumber);
	assert(maybeNumber.has_value());
	std::cout << maybeNumber.value() << std::endl; // won't throw

	return 0;
}
