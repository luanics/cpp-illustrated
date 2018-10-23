#include "luanics/crypto/VigenereCipher.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::crypto {

BEGIN_TEST_SET(VigenereCipher)

TEST(All) {
	// Example borrowed from http://en.wikipedia.org/wiki/Classical_cipher#Substitution_ciphers
	VigenereCipher cipher{"word"};
	auto const plaintext = "I LOVE CRYPTOGRAPHY";
	auto const ciphertext = cipher.encrypt("I LOVE CRYPTOGRAPHY");
	EXPECT_EQ("E ZFYA QIBLHFJNOGKU", ciphertext);
	EXPECT_EQ(plaintext, cipher.decrypt(ciphertext));
}

END_TEST_SET(VigenereCipher)

} // namespace luanics::crypto
