#include "luanics/crypto/Ciphers.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics {
namespace crypto {

BEGIN_TEST_SET(Ciphers)

TEST(Shifted) {
	EXPECT_EQ('c', shift('a', 2));
	EXPECT_EQ('a', shift('y', 2));

	EXPECT_EQ('y', shift('a', -2));
	EXPECT_EQ('a', shift('c', -2));
}

END_TEST_SET(Ciphers)

} // namespace crypto
} // namespace luanics
