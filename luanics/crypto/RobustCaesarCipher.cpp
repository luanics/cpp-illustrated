#include "luanics/crypto/Helpers.hpp"
#include "luanics/crypto/RobustCaesarCipher.hpp"

#include <cctype>

namespace luanics::crypto {

namespace {

std::string process(std::string text, int const key) {
	std::string & result = text;
	for (char & ch: result) {
		ch = robustShift(ch, key);
	}
	return result;
}

}

RobustCaesarCipher::RobustCaesarCipher(int const key) :
	_key{key}
{}

std::string RobustCaesarCipher::encrypt(std::string plaintext) const {
	return process(std::move(plaintext), _key);
}

std::string RobustCaesarCipher::decrypt(std::string ciphertext) const {
	return process(std::move(ciphertext), -_key);
}

} // namespace luanics::crypto
