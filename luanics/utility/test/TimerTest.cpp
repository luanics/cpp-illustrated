#include "luanics/utility/ManualClock.hpp"
#include "luanics/utility/Timer.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::utility {

BEGIN_TEST_SET(Timer)

TEST(All) {
	using ClockType = ManualClock<>;
	ClockType::setNowInNanos(100);
	Timer<ClockType> timer;
	timer.start();
	ClockType::setNowInNanos(110);
	EXPECT_EQ(10, timer.elapsed().count());
}

END_TEST_SET(Timer)

} // namespace luanics::utility
