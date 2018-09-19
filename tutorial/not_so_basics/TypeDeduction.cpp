#include "luanics/testing/Tutorial.hpp"

#include <type_traits>

BEGIN_CHAPTER(TypeDeduction)

SECTION(Review) {

}

SECTION(Basics) {

}

template <typename T, typename U>
bool byValue(U x) {
	return std::is_same<T, U>::value;
}

template <typename T, typename U>
bool byRef(U & x) {
	return std::is_same<T, U>::value;
}

SECTION(BasicAdornments) {
	EXPECT_FALSE((std::is_same<int const &, int>::value));
	int const x = 1;
	// NOTE - placeholder stripped of cvness, just like auto!
	EXPECT_TRUE(byValue<int>(x));
	// Same thing, phrased another way...
	EXPECT_FALSE(byValue<int const>(x));
	// const preserved when it needs to be... (can't bind ref to const ref)
	EXPECT_TRUE(byRef<int const>(x));

	auto & y = x;
	EXPECT_TRUE((std::is_same<decltype(y), const int &>::value));
	// ... therefore auto is deduced to be const int

	EXPECT_TRUE((std::is_same<FIX(int), decltype(x)>::value));
	EXPECT_TRUE((std::is_same<FIX(int), decltype((x))>::value));
}

SECTION(ForwardReferences) {

}

END_CHAPTER(TypeDeduction)
