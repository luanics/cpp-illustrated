#include "luanics/crypto/Helpers.hpp"
#include "luanics/logging/Contract.hpp"
#include "luanics/math/Operations.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <cctype>

namespace {

int constexpr NUM_LETTERS_IN_ENGLISH_ALPHABET = 26;

}

namespace luanics::crypto {

std::int8_t distanceFromA(char const value) {
	EXPECTS(std::islower(value), value);
	return value - 'a';
}

char shift(char const unshifted, int const shift) {
	int const shiftedDistanceFromA = distanceFromA(unshifted) + shift;
	int const wrappedShiftedDistanceFromA = math::positiveModulo(shiftedDistanceFromA, NUM_LETTERS_IN_ENGLISH_ALPHABET);
	return wrappedShiftedDistanceFromA + 'a';
}

char robustShift(char const unshifted, int const shift) {
	return FIX(unshifted);
}

} // namespace luanics::crypto
