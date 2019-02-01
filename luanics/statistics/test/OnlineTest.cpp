#include "luanics/statistics/Online.hpp"
#include "luanics/testing/Unit.hpp"

#include <cmath>

using namespace luanics::testing;

namespace luanics {
namespace statistics {

BEGIN_TEST_SET(OnlineStatistics)

TEST(NoObservations) {
	Online<int> stats;
	EXPECT_EQ(0, stats.count());
	EXPECT_THROW(stats.min());
	EXPECT_THROW(stats.max());
	EXPECT_THROW(stats.mean());
	EXPECT_THROW(stats.stdDev());
}

TEST(SingleObservation) {
	Online<int> stats;
	stats.record(10);
	EXPECT_EQ(1, stats.count());
	EXPECT_EQ(10, stats.min());
	EXPECT_EQ(10, stats.max());
	EXPECT_NEAR(10.0, stats.mean());
	EXPECT_NEAR(0.0, stats.stdDev());
}

TEST(MultipleObservations) {
	Online<int> stats;
	stats.record(10);
	stats.record(20);
	stats.record(30);
	EXPECT_EQ(3, stats.count());
	EXPECT_EQ(10, stats.min());
	EXPECT_EQ(30, stats.max());
	EXPECT_NEAR(20.0, stats.mean());
	EXPECT_NEAR(10.0, stats.stdDev());
}

END_TEST_SET(OnlineStatistics)

} // namespace statistics
} // namespace luanics
