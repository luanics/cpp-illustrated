#include "luanics/profiling/Node.hpp"
#include "luanics/profiling/NodeManager.hpp"
#include "luanics/profiling/ScopedEntrance.hpp"
#include "luanics/profiling/Reporter.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/utility/ManualClock.hpp"

#include <chrono>
#include <iostream>

namespace luanics::profiling {

BEGIN_TEST_SET(NodeManager)

using ClockType = ManualClock<>;
using NodeManagerType = NodeManager<ClockType>;
using NodeType = typename NodeManagerType::NodeType;
using ScopedEntranceType = ScopedEntrance<NodeManagerType>;
using ReporterType = Reporter<ClockType>;

TEST(WithoutScopedEntrance) {
	ClockType::setNowInNanos(100);

	NodeManagerType manager;
	using NameType = NodeManagerType::NameType;

	manager.root()->start();

	ClockType::setNowInNanos(200);
	NameType const child1Name{"child1"};
	manager.enter(child1Name);

	ClockType::setNowInNanos(300);
	manager.exit();

	ClockType::setNowInNanos(400);
	NameType const child2Name{"child2"};
	manager.enter(child2Name);
	ClockType::setNowInNanos(600);
	manager.exit();

	ClockType::setNowInNanos(700);
	manager.enter(child1Name);
	ClockType::setNowInNanos(1000);
	manager.exit();

	ClockType::setNowInNanos(1100);
	manager.root()->stop();

	EXPECT_EQ(1, manager.root()->stats().count());
	EXPECT_EQ(1000, manager.root()->stats().total());

	auto child1 = manager.root()->child(child1Name);
	EXPECT_EQ(2, child1->stats().count());
	EXPECT_EQ(400, child1->stats().total());

	auto child2 = manager.root()->child(child2Name);
	EXPECT_EQ(1, child2->stats().count());
	EXPECT_EQ(200, child2->stats().total());
}

TEST(WithScopedEntrance) {
	ClockType::setNowInNanos(100);

	using NodeManagerType = NodeManager<ClockType>;
	using NameType = NodeManagerType::NameType;

	NodeManagerType manager;
	NameType const child1Name{"child1"};
	NameType const child2Name{"child2"};

	manager.root()->start();

	ClockType::setNowInNanos(200);
	{
		ScopedEntranceType entrance{&manager, child1Name};
		ClockType::setNowInNanos(300);
		// exit
	}

	ClockType::setNowInNanos(400);
	{
		ScopedEntranceType entrance{&manager, child2Name};
		ClockType::setNowInNanos(600);
		// exit
	}

	ClockType::setNowInNanos(700);
	{
		ScopedEntranceType entrance{&manager, child1Name};
		ClockType::setNowInNanos(1000);
		// exit
	}

	ClockType::setNowInNanos(1100);

	manager.root()->stop();

	EXPECT_EQ(1, manager.root()->stats().count());
	EXPECT_EQ(1000, manager.root()->stats().total());

	auto child1 = manager.root()->child(child1Name);
	EXPECT_EQ(2, child1->stats().count());
	EXPECT_EQ(400, child1->stats().total());

	auto child2 = manager.root()->child(child2Name);
	EXPECT_EQ(1, child2->stats().count());
	EXPECT_EQ(200, child2->stats().total());
}

END_TEST_SET(ProfilingNode)

} // namespace luanics::profiling
