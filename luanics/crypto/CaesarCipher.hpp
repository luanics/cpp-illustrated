#pragma once

#include <string>

namespace luanics::crypto {

/// @pre plaintext composed solely of lowercase letters
std::string caesarEncrypt(std::string const & plaintext, int const key);

/// @pre ciphertext composed solely of lowercase letters
std::string caesarDecrypt(std::string const & ciphertext, int const key);

} // namespace luanics::crypto

