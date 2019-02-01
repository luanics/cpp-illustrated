#include "luanics/statistics/Basic.hpp"
#include "luanics/testing/Unit.hpp"

#include <cmath>

using namespace luanics::testing;

namespace luanics {
namespace statistics {

BEGIN_TEST_SET(BasicStatistics)

TEST(NoObservations) {
	Basic<int> stats;
	EXPECT_EQ(0, stats.count());
	EXPECT_EQ(0, stats.total());
}

TEST(SingleObservation) {
	Basic<int> stats;
	stats.record(10);
	EXPECT_EQ(1, stats.count());
	EXPECT_EQ(10, stats.total());
	EXPECT_NEAR(10.0, stats.mean());
}

TEST(MultipleObservations) {
	Basic<int> stats;
	stats.record(10);
	stats.record(20);
	stats.record(30);
	EXPECT_EQ(3, stats.count());
	EXPECT_EQ(60, stats.total());
	EXPECT_NEAR(20.0, stats.mean());
}

END_TEST_SET(BasicStatistics)

} // namespace statistics
} // namespace luanics
