#include "luanics/profiling/Node.hpp"
#include "luanics/statistics/Basic.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/ManualClock.hpp"

#include <chrono>

namespace luanics::profiling {

BEGIN_TEST_SET(ProfilingNode)

using ClockType = ManualClock<>;
using NodeType = Node<ClockType, statistics::Basic>;
using NameType = NodeType::NameType;

TEST(Timing) {
	ClockType::setNowInNanos(1);

	NodeType root{nullptr};

	root.start();
	ClockType::setNowInNanos(11);
	root.stop();

	EXPECT_EQ(1, root.stats().count());
	EXPECT_EQ(10, root.stats().total());
}

TEST(Children) {
	ClockType::setNowInNanos(1);

	NodeType root{nullptr};
	NameType const childName{"child"};
	NodeType * child = root.child(childName);

	child->start();
	ClockType::setNowInNanos(11);
	child->stop();
	EXPECT_EQ(1, child->stats().count());
	EXPECT_EQ(10, child->stats().total());

	ClockType::setNowInNanos(21);
	auto * sameChild = root.child(childName);
	sameChild->start();
	ClockType::setNowInNanos(31);
	sameChild->stop();
	EXPECT_EQ(2, sameChild->stats().count());
	EXPECT_EQ(20, sameChild->stats().total());
}

END_TEST_SET(ProfilingNode)

} // namespace luanics::profiling
