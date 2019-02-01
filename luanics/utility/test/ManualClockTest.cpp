#include "luanics/testing/Unit.hpp"
#include "luanics/utility/ManualClock.hpp"

namespace luanics::utility {

BEGIN_TEST_SET(ManualClock)

TEST(All) {
	using ClockType = ManualClock<>;
	ClockType::setNowInNanos(100);
	auto const start = ClockType::now();
	ClockType::setNowInNanos(110);
	auto const finish = ClockType::now();
	auto const elapsed = finish - start;
	EXPECT_EQ(10, elapsed.count());
}

END_TEST_SET(ManualClock)

} // namespace luanics::utility
