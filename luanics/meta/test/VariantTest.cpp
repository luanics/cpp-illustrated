#include "luanics/meta/Variant.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Orator.hpp"

#include <type_traits>

using namespace luanics::testing;

namespace luanics {
namespace meta {
namespace {

BEGIN_TEST_SET(Variant)

TEST(DefaultConstructor) {
	using NumberType = Variant<int, double>;
	NumberType number;
	EXPECT_FALSE(number.isValid());
	EXPECT_EQ(NumberType::INVALID_INDEX, number.index());
	EXPECT_THROW(get<0>(number));
	EXPECT_THROW(get<int>(number));
}

TEST(ConvertingConstructor) {
	using NumberType = Variant<char, int, double>;

	NumberType character{'a'};
	EXPECT_TRUE(character.isValid());
	EXPECT_EQ(0, character.index());
	EXPECT_EQ('a', get<0>(character));
	EXPECT_EQ('a', get<char>(character));
	EXPECT_THROW(get<int>(character));

	NumberType integer{100};
	EXPECT_TRUE(integer.isValid());
	EXPECT_EQ(1, integer.index());
	EXPECT_EQ(100, get<1>(integer));
	EXPECT_EQ(100, get<int>(integer));
	EXPECT_THROW(get<double>(integer));

	NumberType fp{100.0};
	EXPECT_TRUE(fp.isValid());
	EXPECT_EQ(2, fp.index());
	EXPECT_EQ(100.0, get<2>(fp));
	EXPECT_EQ(100.0, get<double>(fp));
	EXPECT_THROW(get<char>(fp));
}

TEST(AlternativeTypeConstructor) {
	using NumberType = Variant<char, int, float, double>;

	NumberType integer(InPlaceType<int>{}, 'a');
	EXPECT_TRUE(integer.isValid());
	EXPECT_EQ(1, integer.index());
	EXPECT_EQ('a', get<1>(integer));
	EXPECT_EQ('a', get<int>(integer));

	NumberType fp{InPlaceType<float>{}, 100.0};
	EXPECT_TRUE(fp.isValid());
	EXPECT_EQ(2, fp.index());
	EXPECT_EQ(100.0, get<2>(fp));
	EXPECT_EQ(100.0, get<float>(fp));
}

TEST(AlternativeIndexConstructor) {
	using NumberType = Variant<char, int, float, double>;

	NumberType integer(InPlaceIndex<1>{}, 'a');
	EXPECT_TRUE(integer.isValid());
	EXPECT_EQ(1, integer.index());

	NumberType fp{InPlaceIndex<2>{}, 1.0};
	EXPECT_TRUE(fp.isValid());
	EXPECT_EQ(2, fp.index());
}

struct Printer {
	void operator()(char value) {print(value);}
	void operator()(int value) {print(value);}
	void operator()(float value) {print(value);}
	void operator()(double value) {print(value);}
	template <typename T>
	void print(T t) {std::cout << t << std::endl;}
};

struct Counter {
	void operator()(char) {++numChars;}
	void operator()(int) {++numInts;}
	void operator()(float) {++numFloats;}
	void operator()(double) {++numDoubles;}

	unsigned numChars = 0;
	unsigned numInts = 0;
	unsigned numFloats = 0;
	unsigned numDoubles = 0;
};

TEST(Visitor) {
	using NumberType = Variant<char, int, float, double>;
	NumberType number{1};
	Printer printer;
	Counter counter;
//	visit(counter, number);
	visit([&](auto && arg){counter(arg);}, number);
	EXPECT_EQ(1, counter.numInts);
}

END_TEST_SET(Variant)

}
} // namespace meta
} // namespace luanics
