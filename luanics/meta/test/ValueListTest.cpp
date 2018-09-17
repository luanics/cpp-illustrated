#include "luanics/meta/ValueList.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <sstream>

using namespace luanics::testing;

namespace luanics {
namespace meta {
namespace valuelist {
namespace {

template <typename U, typename V>
constexpr bool is_same_v = std::is_same<U,V>::value;

BEGIN_TEST_SET(ValueList)

TEST(Size) {
	using Bools = List<bool, true, false, true>;
	EXPECT_EQ(3, Size<Bools>::value);
	EXPECT_EQ(3, Size_v<Bools>);

	using Empty = List<bool>;
	EXPECT_EQ(0, Size<Empty>::value);
	EXPECT_EQ(0, Size_v<Empty>);
}

TEST(At) {
	using Numbers = List<int, 1, 2, 3>;
	EXPECT_EQ(1, (At<Numbers, 0>::value));
	EXPECT_EQ(1, (At_v<Numbers, 0>));
	EXPECT_EQ(3, (At_v<Numbers, 2>));
}

TEST(Front) {
	using Numbers = List<int, 1, 2, 3>;
	EXPECT_EQ(1, Front<Numbers>::value);
	EXPECT_EQ(1, Front_v<Numbers>);

	using Empty = List<int>;
	// These shouldn't compile...
//	EXPECT_EQ(0, Front<Empty>::value);
//	EXPECT_EQ(0, Front_V<Empty>);
}

//TEST(BadBack) {
//	using Numbers = List<int, 1,2,3>;
//	EXPECT_EQ(3, BadBack<Numbers>::value);
//	EXPECT_EQ(3, BadBack_v<Numbers>);
//}

TEST(Back) {
	using Numbers = List<int, 1,2,3>;
	EXPECT_EQ(3, Back<Numbers>::value);
	EXPECT_EQ(3, Back_v<Numbers>);

	using Empty = List<int>;
	// These shouldn't compile...
//	EXPECT_EQ(0, Back<Empty>::value);
//	EXPECT_EQ(0, Back_V<Empty>);
}

TEST(PushFront) {
	using Ints123 = List<int, 1, 2, 3>;
	using Ints0123 = List<int, 0, 1, 2, 3>;
	EXPECT_TRUE((is_same_v<Ints0123, typename PushFront<Ints123, 0>::type>));
	EXPECT_TRUE((is_same_v<Ints0123, PushFront_t<Ints123, 0>>));

	using Empty = List<int>;
	using Ints0 = List<int, 0>;
	EXPECT_TRUE((is_same_v<Ints0, PushFront_t<Empty, 0>>));
}

TEST(PushBack) {
	using Ints123 = List<int, 1, 2, 3>;
	using Ints1234 = List<int, 1, 2, 3, 4>;
	EXPECT_TRUE((is_same_v<Ints1234, typename PushBack<Ints123, 4>::type>));
	EXPECT_TRUE((is_same_v<Ints1234, PushBack_t<Ints123, 4>>));

	using Empty = List<int>;
	using Ints0 = List<int, 0>;
	EXPECT_TRUE((is_same_v<Ints0, PushBack_t<Empty, 0>>));
}

TEST(PopFront) {
	using Ints0123 = List<int, 0, 1, 2, 3>;
	using Ints123 = List<int, 1, 2, 3>;
	EXPECT_TRUE((is_same_v<Ints123, typename PopFront<Ints0123>::type>));
	EXPECT_TRUE((is_same_v<Ints123, PopFront_t<Ints0123>>));

	using Ints0 = List<int, 0>;
	using Empty = List<int>;
	EXPECT_TRUE((is_same_v<Empty, PopFront_t<Ints0>>));
}

TEST(PopBack) {
	using Ints1234 = List<int, 1, 2, 3, 4>;
	using Ints123 = List<int, 1, 2, 3>;
	EXPECT_TRUE((is_same_v<Ints123, typename PopBack<Ints1234>::type>));
	EXPECT_TRUE((is_same_v<Ints123, PopBack_t<Ints1234>>));

	using Ints0 = List<int, 0>;
	using Empty = List<int>;
	EXPECT_TRUE((is_same_v<Empty, PopBack_t<Ints0>>));
}

template <int InputV>
struct Double {
	static constexpr int value = 2 * InputV;
};

TEST(Transform) {
	using Ints123 = List<int, 1, 2, 3>;
	using Ints246 = List<int, 2, 4, 6>;

	EXPECT_TRUE((is_same_v<Ints246, typename Transform<Ints123, Double>::type>));
	EXPECT_TRUE((is_same_v<Ints246, Transform_t<Ints123, Double>>));

	using Empty = List<int>;
	EXPECT_TRUE((is_same_v<Empty, Transform_t<Empty, Double>>));
}

TEST(Printer) {
	using Ints123 = List<int, 1, 2, 3>;
	std::ostringstream out;
	Printer<Ints123>::printTo(out);
	EXPECT_EQ("1 2 3 ", out.str());
}

//template <template <int> class PredicateT>
//struct Not {
//	static constexpr bool value = not InputV;
//};

TEST(Find) {
	using Ints123 = List<int, 1, 2, 3, 1, 2, 3>;
	EXPECT_EQ(0, (Find_v<Ints123, 1>));
	EXPECT_EQ(2, (Find_v<Ints123, 3>));
	// Won't compile ...
//	EXPECT_EQ(0, (Find_v<Ints123, 4>));
}

template <int InputV>
struct IsEven {
	static constexpr int value = InputV % 2 == 0;
};

TEST(IndexWhere) {
	using Ints123 = List<int, 1, 2, 3>;
	EXPECT_EQ(1, (IndexWhere_v<Ints123, IsEven>));
}

TEST(CountIf) {
	using Ints123 = List<int, 1, 2, 3>;
	using Ints234 = List<int, 2, 3, 4>;
	EXPECT_EQ(1, (CountIf_v<Ints123, IsEven>));
	EXPECT_EQ(2, (CountIf_v<Ints234, IsEven>));
}

TEST(Count) {
	using Ints = List<int, 1, 2, 2, 3>;
	EXPECT_EQ(0, (Count_v<Ints,5>));
	EXPECT_EQ(2, (Count_v<Ints,2>));
}

END_TEST_SET(ValueList)

}
} // namespace value
} // namespace meta
} // namespace luanics
