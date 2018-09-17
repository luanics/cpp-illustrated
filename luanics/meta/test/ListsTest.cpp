#include "luanics/meta/Lists.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <type_traits>

namespace luanics {
namespace meta {
namespace {

template <typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

BEGIN_TEST_SET(Lists)

template <typename T>
struct SizeOf {
	static constexpr std::size_t value = sizeof(T);
};


TEST(TypeToValue) {
	using Types = typelist::List<int8_t, int16_t, int32_t, int64_t>;
	using Sizes = valuelist::List<std::size_t, 1, 2, 4, 8>;
	using Sizes2 = valuelist::List<std::size_t, 1, 2, 4, 8>;
	using Transformed = TypeToValue_t<Types, SizeOf>;
	valuelist::Printer<Transformed>::printTo(std::cout);
	EXPECT_EQ(4, valuelist::Size_v<Transformed>);
	EXPECT_TRUE((is_same_v<std::size_t, valuelist::Type_t<Transformed>>));
	EXPECT_EQ(1, (valuelist::At_v<Transformed, 0>));
	EXPECT_EQ(2, (valuelist::At_v<Transformed, 1>));
	EXPECT_EQ(4, (valuelist::At_v<Transformed, 2>));
	EXPECT_EQ(8, (valuelist::At_v<Transformed, 3>));
	EXPECT_TRUE((is_same_v<Sizes, Sizes2>));
	EXPECT_TRUE((is_same_v<Sizes, Transformed>));
}

END_TEST_SET(Lists)

}
} // namespace meta
} // namespace luanics
