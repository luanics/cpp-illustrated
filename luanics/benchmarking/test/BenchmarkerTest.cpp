#include "luanics/benchmarking/Benchmarker.hpp"
#include "luanics/testing/Unit.hpp"

#include <cmath>

using namespace luanics::testing;

namespace luanics::benchmarking {

BEGIN_TEST_SET(Benchmarker)

TEST(EmptySubject) {
	Benchmarker benchmarker{[]{}, 10, 100, false};
	EXPECT_EQ(10, benchmarker.numTrials());
	EXPECT_EQ(100, benchmarker.numIterationsPerTrial());
}

END_TEST_SET(Benchmarker)

} // namespace luanics::benchmarking
