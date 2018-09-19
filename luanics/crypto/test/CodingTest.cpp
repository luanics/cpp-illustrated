#include "luanics/crypto/Coding.hpp"
#include "luanics/testing/Unit.hpp"

#include <climits>
#include <iostream>
#include <sstream>

namespace luanics {
namespace crypto {

BEGIN_TEST_SET(Coding)

auto constexpr shift = std::numeric_limits<std::string::value_type>::digits;

TEST(EncodeOneChar) {
	std::string const decoded{"H"};
	IntegerType const encoded = encode(decoded);
	IntegerType const expected = static_cast<IntegerType>('H');
	EXPECT_EQ(expected, encoded);
}

TEST(EncodeTwoChars) {
	std::string const decoded{"Hi"};
	IntegerType const encoded = encode(decoded);
	IntegerType const expected =
		(static_cast<IntegerType>('H') << shift)
		+ static_cast<IntegerType>('i');
	EXPECT_EQ(expected, encoded);
}

TEST(DecodeOneChar) {
	IntegerType const encoded = static_cast<IntegerType>('H');
	std::string const decoded = decode(encoded);
	std::string const expected = "H";
	EXPECT_EQ(expected, decoded);
}

TEST(DecodeTwoChars) {
	IntegerType const encoded =
		(static_cast<IntegerType>('H') << shift)
		+ static_cast<IntegerType>('i');
	std::string const decoded = decode(encoded);
	std::string const expected = "Hi";
	EXPECT_EQ(expected, decoded);
}

TEST(RoundtripSmall) {
	std::string const message{"Hi there"};
	auto const encoded = encode(message);
	auto const decoded = decode(encoded);
	EXPECT_EQ(message, decoded);
}

TEST(RoundtripBig) {
	std::string const message{"Hi there, this message is too long."};
	auto const encoded = encode(message);
	auto const decoded = decode(encoded);
	std::string const expected{"Hi there,"};
	EXPECT_EQ(expected, decoded);
}

END_TEST_SET(Encode)

} // namespace crypto
} // namespace luanics
