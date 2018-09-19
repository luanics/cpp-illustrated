#include "luanics/crypto/Math.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Tuples.hpp"

#include <climits>
#include <limits>

namespace luanics {
namespace crypto {

BEGIN_TEST_SET(CryptoMath)

TEST(AreCoprime) {
	EXPECT_FALSE(areCoprime(4,6));
	EXPECT_TRUE(areCoprime(5,7));
}

TEST(SlowExp) {
	EXPECT_EQ(1, slowExp(10,0));
	EXPECT_EQ(10, slowExp(10,1));
	EXPECT_EQ(100, slowExp(10,2));
	EXPECT_EQ(1000, slowExp(10,3));
}

TEST(UnfastExp) {
	EXPECT_EQ(1, unfastExp(10,0));
	EXPECT_EQ(10, unfastExp(10,1));
	EXPECT_EQ(100, unfastExp(10,2));
	EXPECT_EQ(1000, unfastExp(10,3));
}

TEST(FastExp) {
	EXPECT_EQ(1, fastExp(10,0));
	EXPECT_EQ(10, fastExp(10,1));
	EXPECT_EQ(100, fastExp(10,2));
	EXPECT_EQ(1000, fastExp(10,3));
}

//TEST(FasterExp) {
//	EXPECT_EQ(1, fasterExp(10,0));
//	EXPECT_EQ(10, fasterExp(10,1));
//	EXPECT_EQ(100, fasterExp(10,2));
//	EXPECT_EQ(1000, fasterExp(10,3));
//}

TEST(SlowModExp) {
	EXPECT_EQ(1, slowModExp(9,2,10));
	EXPECT_EQ(1, slowModExp(9,10,11));
	EXPECT_EQ(445, slowModExp(4,13,497));
}

TEST(FastModExp) {
	EXPECT_EQ(1, fastModExp(9,2,10));
	EXPECT_EQ(1, fastModExp(9,10,11));
	EXPECT_EQ(445, fastModExp(4,13,497));
}

TEST(FermatPrime) {
	EXPECT_EQ(3, fermatPrime(0));
	EXPECT_EQ(5, fermatPrime(1));
	EXPECT_EQ(17, fermatPrime(2));
	EXPECT_EQ(257, fermatPrime(3));
	EXPECT_EQ(65537, fermatPrime(4));
}

TEST(ExtendedEuclidean) {
	EXPECT_EQ(std::make_tuple(21, 3,-22), extendedEuclidean(1239,168));
}

END_TEST_SET(CryptoMath)

} // namespace crypto
} // namespace luanics
