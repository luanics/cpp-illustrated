#pragma once

#include <random>
#include <string>

namespace luanics::crypto {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class StreamCipher
///
/// @brief Simple stream cipher using byte-wise encryption.
///
/// Note that this is for demonstration purposes only and is *not*
///  a cryptographically sound implementation.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class StreamCipher {
public:
	StreamCipher(std::size_t seed = std::random_device{}());
	void setSeed(std::size_t seed);

	std::string encrypt(std::string plaintext);
	std::string decrypt(std::string ciphertext);

private:
	std::mt19937 _engine;
}; // class StreamCipher

} // namespace luanics::crypto
