#pragma once

#include <cstdint>
#include <string>

namespace luanics::crypto {

/// @returns the distance of value from 'a'
/// @pre ch is lowercase letter
std::int8_t distanceFromA(char const value);

/// Shifts the "unshifted" character by "shift" letters in the wrapped English alphabet
/// @pre unshifted is lowercase letter
char shift(char const unshifted, int const key);

/// Shifts the "unshifted" character by "shift" letters in the wrapped English alphabet
///  if it is a letter, else (number or symbol) leaves it untouched.
///  Maintains capitalization.
char robustShift(char const unshifted, int const key);

} // namespace luanics::crypto
