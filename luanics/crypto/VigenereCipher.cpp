#include "luanics/crypto/Helpers.hpp"
#include "luanics/crypto/VigenereCipher.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <cctype>

namespace luanics::crypto {

VigenereCipher::VigenereCipher(std::string key) :
	_key{std::move(key)}
{}

std::string VigenereCipher::encrypt(std::string decoded) const {
	CREATE
	return decoded;
}

std::string VigenereCipher::decrypt(std::string encoded) const {
	CREATE
	return encoded;
}

} // namespace luanics::crypto
