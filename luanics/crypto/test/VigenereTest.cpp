#include "luanics/crypto/Vigenere.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics {
namespace crypto {

BEGIN_TEST_SET(Vigenere)

TEST(All) {
	// Example borrowed from http://en.wikipedia.org/wiki/Classical_cipher#Substitution_ciphers
	Vigenere cipher{"word"};
	auto const decoded = "I LOVE CRYPTOGRAPHY";
	auto const encoded = cipher.encrypt("I LOVE CRYPTOGRAPHY");
	EXPECT_EQ("E ZFYA QIBLHFJNOGKU", encoded);
	EXPECT_EQ(decoded, cipher.decrypt(encoded));
}

END_TEST_SET(Vigenere)

} // namespace crypto
} // namespace luanics
