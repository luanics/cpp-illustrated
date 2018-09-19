#include "luanics/crypto/Vigenere.hpp"
#include "luanics/crypto/Ciphers.hpp"

#include <cctype>

namespace luanics {
namespace crypto {

Vigenere::Vigenere(std::string key) :
	_key{std::move(key)}
{}

std::string Vigenere::encrypt(std::string decoded) const {
	// Operate inplace on decoded
	std::size_t keyIndex = 0;
	for (char & ch: decoded) {
		if (std::isalpha(ch)) {
			ch = shift(ch, _key[keyIndex++ % _key.size()] - 'a');
		}
	}
	return decoded;
}

std::string Vigenere::decrypt(std::string encoded) const {
	// Operate inplace on encoded
	std::size_t keyIndex = 0;
	for (char & ch: encoded) {
		if (std::isalpha(ch)) {
			ch = shift(ch, -(_key[keyIndex++ % _key.size()] - 'a'));
		}
	}
	return encoded;
}

}  // namespace crypto
}  // namespace luanics
