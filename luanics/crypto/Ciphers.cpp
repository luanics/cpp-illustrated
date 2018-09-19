#include "luanics/crypto/Ciphers.hpp"
#include "luanics/math/Operations.hpp"

#include <cctype>

namespace {

int constexpr NUM_LETTERS_IN_ENGLISH_ALPHABET = 26;

}

namespace luanics {
namespace crypto {

// TODO: constexpr version
char shift(char const unshifted, int const shift) {
	bool const isUpper = std::isupper(unshifted);
	int const lowered = std::tolower(unshifted);
	int result = math::modulo(lowered - 'a' + shift, NUM_LETTERS_IN_ENGLISH_ALPHABET) + 'a';
	return isUpper ? std::toupper(result) : result;
}

}  // namespace crypto
}  // namespace luanics
