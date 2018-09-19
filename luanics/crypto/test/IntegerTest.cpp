#include "luanics/crypto/Integer.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <sstream>

namespace luanics {
namespace crypto {

BEGIN_TEST_SET(Integer)

TEST(DefaultConstructor) {
	Integer zero;
	EXPECT_TRUE(zero.isZero());
	EXPECT_FALSE(zero.isPositive());
	EXPECT_FALSE(zero.isNegative());
}

TEST(MultipleDigitContructor) {
	Integer fromDigits{true, {1,2,3}};
	EXPECT_FALSE(fromDigits.isZero());
	EXPECT_TRUE(fromDigits.isPositive());
	EXPECT_FALSE(fromDigits.isNegative());
	EXPECT_EQ(1, fromDigits.digitAt(0));
	EXPECT_EQ(2, fromDigits.digitAt(1));
	EXPECT_EQ(3, fromDigits.digitAt(2));
}

TEST(NegativeMultipleDigitContructor) {
	Integer fromDigits{false, {1,2,3}};
	EXPECT_FALSE(fromDigits.isZero());
	EXPECT_FALSE(fromDigits.isPositive());
	EXPECT_TRUE(fromDigits.isNegative());
	EXPECT_EQ(1, fromDigits.digitAt(0));
	EXPECT_EQ(2, fromDigits.digitAt(1));
	EXPECT_EQ(3, fromDigits.digitAt(2));
}

TEST(SmallDecimalValueConstructor) {
	Integer const fromValue{10};
	EXPECT_FALSE(fromValue.isZero());
	EXPECT_TRUE(fromValue.isPositive());
	EXPECT_FALSE(fromValue.isNegative());
	EXPECT_EQ(1, fromValue.numDigits());
	EXPECT_EQ(10, fromValue.digitAt(0));
}

TEST(SmallNegativeDecimalValueConstructor) {
	Integer const fromValue{-10};
	EXPECT_FALSE(fromValue.isZero());
	EXPECT_FALSE(fromValue.isPositive());
	EXPECT_TRUE(fromValue.isNegative());
	EXPECT_EQ(1, fromValue.numDigits());
	EXPECT_EQ(10, fromValue.digitAt(0));
}

TEST(LargeDecimalValueConstructor) {
	Integer const fromValue{127342};
	Integer const fromDigits{true, {61806,1}};
	EXPECT_FALSE(fromValue.isZero());
	EXPECT_TRUE(fromValue.isPositive());
	EXPECT_FALSE(fromValue.isNegative());
	EXPECT_EQ(fromDigits, fromValue);
}

TEST(Queries) {
	Integer zero;
	EXPECT_TRUE(zero.isZero());
	EXPECT_FALSE(zero.isNegative());

	Integer positive{true, {1}};
	EXPECT_FALSE(positive.isZero());
	EXPECT_FALSE(positive.isNegative());

	Integer negative{false, {1}};
	EXPECT_FALSE(negative.isZero());
	EXPECT_TRUE(negative.isNegative());
}

TEST(Modification) {
	Integer one{true, {1}};
	one.negate();
	EXPECT_TRUE(one.isNegative());
	one.makePositive();
	EXPECT_FALSE(one.isNegative());
	Integer negativeOne = -one;
	EXPECT_TRUE(negativeOne.isNegative());
}

TEST(Comparison) {
	Integer oneOne{true, {1,1}};
	Integer alsoOneOne{true, {1,1}};
	Integer twoTwo{true, {2,2}};
	EXPECT_TRUE(oneOne == alsoOneOne);
	EXPECT_FALSE(oneOne == twoTwo);
	EXPECT_TRUE(oneOne < twoTwo);
	EXPECT_FALSE(oneOne > twoTwo);
}

TEST(SingleDigitAddition) {
	Integer one{true, {1}};
	Integer two{true, {2}};
	Integer three{true, {3}};

	EXPECT_EQ(three, one + two);
}

TEST(MultipleDigitAddition) {
	Integer const one{true, {1}};
	Integer const oneOne{true, {1,1}};
	Integer const twoTwo{true, {2,2}};
	Integer const threeThree{true, {3,3}};
	Integer const twoOne{true, {2,1}};
	Integer const zeroTwo{true, {0,2}};

	EXPECT_EQ(threeThree, oneOne + twoTwo);

	// Force a carry
	Integer const max{true, {Integer::MaxDigitValue}};
	EXPECT_EQ(zeroTwo, oneOne + max);

	Integer const zeroZeroFive{true, {0,0,5}};
	Integer maxMaxLessOneFour{true, {Integer::MaxDigitValue, Integer::MaxDigitValue, 4}};

	EXPECT_EQ(zeroZeroFive, one + maxMaxLessOneFour);
}

TEST(MultipleDigitAddition2) {
	Integer const x{true, {24000,15096,18132,41989,22768,17571,33729,26997,8647,44049,9353,4664}};
	Integer const y{true, {8,7,14,2337,898}};
	Integer const expected{true, {24008,15103,18146,44326,23666,17571,33729,26997,8647,44049,9353,4664}};
	EXPECT_EQ(expected, x + y);
}

TEST(Subtraction) {
	Integer const x{true, {6,2,1,0,0,1}};
	Integer const y{true, {8,2,1}};
	Integer const expected{true, {65534,65535,65535,65535,65535}};
	EXPECT_EQ(expected, x - y);
}

TEST(TimesBaseToN) {
	Integer one{true,{1}};
	Integer oneTimesBaseTo3 = timesBaseToN(one,3);
	Integer expected{true, {0,0,0,1}};
	EXPECT_EQ(oneTimesBaseTo3, expected);
}

TEST(Multiplication) {
	Integer const x{true, {33000,57000,65535}};
	Integer const y{true, {5,2}};
	Integer const expected{true, {33928,23322,48464,4,2}};
	EXPECT_EQ(expected, x * y);
}

TEST(Multiplication2) {
	Integer const x{true, {22135,35438,15031}};
	Integer const y{true, {542,327}};
	Integer const expected{true, {4082,34716,9095,238,75}};
	EXPECT_EQ(expected, x * y);
}

TEST(Multiplication3) {
	Integer const x{true, {8,5,6,429,87,328,4,2}};
	Integer const y{true, {3000,12,9,7,2332}};
	Integer const expected{true, {24000,15096,18132,41989,22768,17571,33729,26997,8647,44049,9353,4664}};
	EXPECT_EQ(expected, x * y);
}

TEST(DivideEqualsWithSingleDigit) {
	Integer dividend{true, {62,58042,712,6238}};
	Integer const expected{true, {32783,14510,32946,1559}};
	EXPECT_EQ(expected, dividend /= 4);
}

TEST(NormalizeDivisor) {
	Integer const four{true, {4}};
	Integer::DigitType expected = 13107;
	EXPECT_EQ(expected, normalizeDivisor(four));
}

TEST(DivideWithSingleDigit) {
	Integer const dividend{true, {62,58042,712,6238}};
	Integer const divisor{true, {4}};
	Integer const expected{true, {32783,14510,32946,1559}};
	EXPECT_EQ(expected, dividend / divisor);
}

TEST(DivideWithMultipleDigits) {
	Integer const dividend{true, {6,34870,9095,238,75}};
	Integer const divisor{true, {542,327}};
	Integer const expected{true, {22135,35438,15031}};
	EXPECT_EQ(expected, dividend / divisor);
}

TEST(DivideWithMultipleDigits2) {
//	Integer const x{true,{24000,15096,18132,41989,22768,17571,33729,26997,8647,44049,9353,4664}};
//	Integer const y{true,{8,7,14,2337,898}};
	Integer const dividend{true, {24008,15103,18146,44326,23666,17571,33729,26997,8647,44049,9353,4664}};
	Integer const divisor{true, {8,5,6,429,87,328,4,2}};
	Integer const expected{true, {3000,12,9,7,2332}};
	EXPECT_EQ(expected, dividend / divisor);
}

TEST(Modulo) {
	Integer const dividend{true, {6,34870,9095,238,75}};
	Integer const divisor{true, {542, 327}};
	Integer const expected{true, {61460, 153}};
	EXPECT_EQ(expected, dividend % divisor);
}

TEST(Modulo2) {
	Integer const dividend{true, {24008,15103,18146,44326,23666,17571,33729,26997,8647,44049,9353,4664}};
	Integer const divisor{true, {8,5,6,429,87,328,4,2}};
	Integer const expected{true, {8,7,14,2337,898}};
	EXPECT_EQ(expected, dividend % divisor);
}

TEST(PrintAsNative) {
	Integer const value{false, {1,2,3}};
	std::ostringstream out;
	printAsNative(value, out);
	EXPECT_EQ("-{1,2,3,}", out.str());
}

TEST(SingleDigitOutput) {
	Integer const ten{10};
	std::ostringstream out;
	out << ten;
	EXPECT_EQ("10", out.str());
}

TEST(NegativeSingleDigitOutput) {
	Integer const minusTen{-10};
	std::ostringstream out;
	out << minusTen;
	EXPECT_EQ("-10", out.str());
}

TEST(DoubleDigitOutput) {
	Integer const value{127342};
	std::ostringstream out;
	out << value;
	EXPECT_EQ("127342", out.str());
}

TEST(NegativeDoubleDigitOutput) {
	Integer const value{-127342};
	std::ostringstream out;
	out << value;
	EXPECT_EQ("-127342", out.str());
}

TEST(QuadDigitOutput) {
	Integer const source{-9000000000000000001ll};
	std::ostringstream out;
	out << source;
	EXPECT_EQ("-9000000000000000001", out.str());
}

TEST(SingleDigitInput) {
	std::istringstream in{"10"};
	Integer destination;
	in >> destination;
	EXPECT_EQ(Integer{10}, destination);
}

TEST(NegativeSingleDigitInput) {
	std::istringstream in{"-10"};
	Integer destination;
	in >> destination;
	EXPECT_EQ(Integer{-10}, destination);
}

TEST(BigArithmetic) {
	EXPECT_EQ(
		Integer{"1000000000000000000000000000"},
		Integer{"999999999999999999999999999"} + Integer{"1"}
	);
	EXPECT_EQ(
		Integer{"1000000000000000000000000000000000000000000000000000000"},
		Integer{"1000000000000000000000000000"} * Integer{"1000000000000000000000000000"}
	);
	EXPECT_EQ(
		Integer{"1000000000000000000000000000"},
		Integer{"1000000000000000000000000000000000000000000000000000000"} / Integer{"1000000000000000000000000000"}
	);
}

END_TEST_SET(Integer)

} // namespace crypto
} // namespace luanics
