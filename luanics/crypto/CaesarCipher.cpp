#include "luanics/crypto/CaesarCipher.hpp"
#include "luanics/crypto/Helpers.hpp"
#include "luanics/logging/Contract.hpp"

namespace luanics::crypto {

std::string caesarEncrypt(std::string const & plaintext, int const key) {
	std::string result{plaintext};
	for (char & ch: result) {
		ch = shift(ch, key);
	}
	return result;
}

std::string caesarDecrypt(std::string const & ciphertext, int const key) {
	return caesarEncrypt(ciphertext, -key);
}

} // namespace luanics::crypto
