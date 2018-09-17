#include "luanics/meta/Detection.hpp"
#include "luanics/testing/Unit.hpp"

#include <iostream>
#include <type_traits>

namespace luanics {
namespace {

BEGIN_TEST_SET(Detection)

template <typename T>
using Increment_t = decltype(++std::declval<T&>());

template<typename T>
using Ostream_t = decltype(std::declval<std::ostream &>() << std::declval<T>());

class Empty {};

TEST(All) {
	bool const isIncrementable = IsDetected_v<Increment_t, int>;
	EXPECT_TRUE(isIncrementable);

	bool const isEmptyIncrementable = IsDetected_v<Increment_t, Empty>;
	EXPECT_FALSE(isEmptyIncrementable);

	bool const isIntOstreamable = IsDetected_v<Ostream_t, int>;
	EXPECT_TRUE(isIntOstreamable);

	bool const isEmptyOstreamable = IsDetected_v<Ostream_t, Empty>;
	EXPECT_FALSE(isEmptyOstreamable);

	bool const isVoidOstreamable = IsDetected_v<Ostream_t, void>;
	EXPECT_FALSE(isVoidOstreamable);
}

END_TEST_SET(Detection)

} // namespace
} // namespace luanics
