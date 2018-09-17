#include "luanics/meta/TypeList.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstdint>
#include <type_traits>

using namespace luanics::testing;

namespace luanics {
namespace meta {
namespace typelist {
namespace {

struct A {};
struct B {};
struct C {};
struct D {};
struct E {};

template <typename U, typename V>
constexpr bool is_same_v = std::is_same<U,V>::value;

BEGIN_TEST_SET(TypeList)

TEST(IsEmpty) {
	using Empty = List<>;
	EXPECT_TRUE(IsEmpty<Empty>::value);
	EXPECT_TRUE(IsEmpty_v<Empty>);

	using a = List<A>;
	EXPECT_FALSE(IsEmpty<a>::value);
	EXPECT_FALSE(IsEmpty_v<a>);
}

TEST(Size) {
	using Empty = List<>;
	EXPECT_EQ(0, Size<Empty>::value);
	EXPECT_EQ(0, Size_v<Empty>);

	using a = List<A>;
	EXPECT_EQ(1, Size<a>::value);
	EXPECT_EQ(1, Size_v<a>);

	using abc = List<A, B, C>;
	EXPECT_EQ(3, Size<abc>::value);
	EXPECT_EQ(3, Size_v<abc>);
}

TEST(Front) {
	using abc = List<A, B, C>;
	EXPECT_TRUE((is_same_v<typename Front<abc>::type, A>));
	EXPECT_TRUE((is_same_v<Front_t<abc>, A>));
}

TEST(Back) {
	using abc = List<A, B, C>;
	EXPECT_TRUE((is_same_v<typename Back<abc>::type, C>));
	EXPECT_TRUE((is_same_v<Back_t<abc>, C>));
}

TEST(PushFront) {
	using empty = List<>;
	using a = List<A>;
	using b = List<B>;
	using ab = List<A, B>;

	EXPECT_TRUE((is_same_v<typename PushFront<A, empty>::type, a>));
	EXPECT_TRUE((is_same_v<PushFront_t<A, empty>, a>));

	EXPECT_TRUE((is_same_v<typename PushFront<A, b>::type, ab>));
	EXPECT_TRUE((is_same_v<PushFront_t<A, b>, ab>));
}

TEST(PushBack) {
	using empty = List<>;
	using a = List<A>;
	using ab = List<A, B>;

	EXPECT_TRUE((is_same_v<typename PushBack<A, empty>::type, a>));
	EXPECT_TRUE((is_same_v<PushBack_t<A, empty>, a>));

	EXPECT_TRUE((is_same_v<typename PushBack<B, a>::type, ab>));
	EXPECT_TRUE((is_same_v<PushBack_t<B, a>, ab>));
}

TEST(PopFront) {
	using empty = List<>;
	using a = List<A>;
	using b = List<B>;
	using ab = List<A, B>;

	EXPECT_TRUE((is_same_v<typename PopFront<a>::type, empty>));
	EXPECT_TRUE((is_same_v<PopFront_t<a>, empty>));

	EXPECT_TRUE((is_same_v<typename PopFront<ab>::type, b>));
	EXPECT_TRUE((is_same_v<PopFront_t<ab>, b>));
}

TEST(PopBack) {
	using empty = List<>;
	using a = List<A>;
	using ab = List<A, B>;

	EXPECT_TRUE((is_same_v<typename PopBack<a>::type, empty>));
	EXPECT_TRUE((is_same_v<PopBack_t<a>, empty>));

	EXPECT_TRUE((is_same_v<typename PopBack<ab>::type, a>));
	EXPECT_TRUE((is_same_v<PopBack_t<ab>, a>));
}

TEST(TypeAt) {
	using abc = List<A, B, C>;
	EXPECT_TRUE((is_same_v<TypeAt_t<0, abc>, A>));
}

TEST(IndexOf) {
	using abc = List<A, B, C>;
	EXPECT_EQ(0, (IndexOf_v<A, abc>));
	EXPECT_EQ(2, (IndexOf_v<C, abc>));
}

TEST(IndexWhere) {
	using BoolIntDoubleFloat = List<bool, int, double, float>;
	EXPECT_EQ(0, (IndexWhere_v<std::is_integral, BoolIntDoubleFloat>));
	EXPECT_EQ(2, (IndexWhere_v<std::is_floating_point, BoolIntDoubleFloat>));
}


TEST(Transform) {
	using With = List<bool &, int &, float &>;
	using Without = List<bool, int, float>;
	EXPECT_TRUE((is_same_v<Without, typename Transform<std::remove_reference, With>::type>));
}

TEST(OverloadChooser) {
	using Types = List<int, float>;
	EXPECT_TRUE((is_same_v<float, OverloadChooser_t<float, Types>>));
}

END_TEST_SET(TypeList)

}
} // namespace typelist
} // namespace meta
} // namespace luanics
