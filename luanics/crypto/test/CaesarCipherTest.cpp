#include "luanics/crypto/CaesarCipher.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::crypto {

BEGIN_TEST_SET(CaesarCipher)

TEST(ValidInput) {
	int const key = 2;
	std::string const plaintext{"ilovecryptography"};
	std::string const ciphertext = caesarEncrypt(plaintext, key);
	EXPECT_EQ("knqxgetarvqitcrja", ciphertext);
	EXPECT_EQ(plaintext, caesarDecrypt(ciphertext, key));
}

// This version of the cipher requires strings be composed solely of lowercase letters.
TEST(InvalidInput) {
	int const key = 2;

	EXPECT_THROW(caesarEncrypt("ThisHasUppercaseLetters", key));
	EXPECT_THROW(caesarDecrypt("ThisHasUppercaseLetters", key));

	EXPECT_THROW(caesarEncrypt("this has spaces", key));
	EXPECT_THROW(caesarDecrypt("this has spaces", key));

	EXPECT_THROW(caesarEncrypt("th1sh4snumb3rs", key));
	EXPECT_THROW(caesarDecrypt("th1sh4snumb3rs", key));

	EXPECT_THROW(caesarEncrypt("th!sh@sch@r@cter$", key));
	EXPECT_THROW(caesarDecrypt("th!sh@sch@r@cter$", key));
}

END_TEST_SET(CaesarCipher)

} // namespace luanics::crypto
