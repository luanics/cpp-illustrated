#include "luanics/testing/core/Outcome.hpp"

namespace luanics::testing::core {

namespace {
	constexpr auto NONE_STRING = "NONE";
	constexpr auto PASS_STRING = "PASS";
	constexpr auto FAIL_STRING = "FAIL";
	constexpr auto ERROR_STRING = "ERROR";
}

Outcome combined(Outcome const lhs, Outcome const rhs) {
	if (lhs <= Outcome::NONE and rhs <= Outcome::NONE) {
		return Outcome::NONE;
	}
	else if (lhs <= Outcome::PASS and rhs <= Outcome::PASS) {
		return Outcome::PASS;
	}
	else if (lhs <= Outcome::FAIL and rhs <= Outcome::FAIL) {
		return Outcome::FAIL;
	}
	else {
		return Outcome::ERROR;
	}
}

std::ostream & operator<<(std::ostream & out, Outcome const outcome) {
	switch (outcome) {
		case Outcome::NONE: out << NONE_STRING; break;
		case Outcome::PASS: out << PASS_STRING; break;
		case Outcome::FAIL: out << FAIL_STRING; break;
		case Outcome::ERROR: out << ERROR_STRING; break;
	}
	return out;
}

} // namespace luanics::testing::core
