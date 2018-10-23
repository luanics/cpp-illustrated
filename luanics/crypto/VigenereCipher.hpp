#pragma once

#include <string>

namespace luanics::crypto {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class VigenereCipher
///
/// @brief Implementation of the Vigenere cipher.
///
/// Works only with plaintext composed solely of lowercase letters.
/// See http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class VigenereCipher {
public:
	/// @param key determines the alphabetical shifts applied
	VigenereCipher(std::string key);

	/// @pre plaintext composed solely of lowercase letters
	std::string encrypt(std::string plaintext) const;
	/// @pre ciphertext composed solely of lowercase letters
	std::string decrypt(std::string ciphertext) const;

private:
	std::string _key;
}; // class VigenereCipher

} // namespace luanics::crypto
