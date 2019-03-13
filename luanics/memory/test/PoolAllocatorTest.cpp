#include "luanics/memory/PoolAllocator.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstring>
#include <sstream>

namespace luanics {
namespace memory {

BEGIN_TEST_SET(PoolAllocator)

TEST(PushBack) {
	std::list<int, luanics::memory::PoolAllocator<int, 2>> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.front());
	EXPECT_EQ(3, l.back());

	l.push_back(4);
	l.push_back(5);
	EXPECT_EQ(5, l.size());
	EXPECT_EQ(1, l.front());
	EXPECT_EQ(5, l.back());;
}

TEST(PushAndPopBack) {
	std::list<int, luanics::memory::PoolAllocator<int, 2>> l;
	l.push_back(1);
	l.push_back(2);
	l.pop_back();
	EXPECT_EQ(1, l.size());
	EXPECT_EQ(1, l.front());
	EXPECT_EQ(1, l.back());

	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.pop_back();
	l.pop_back();
	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.front());
	EXPECT_EQ(3, l.back());

	l.push_back(4);
	l.push_back(5);
	EXPECT_EQ(5, l.size());
	EXPECT_EQ(1, l.front());
	EXPECT_EQ(5, l.back());
}

TEST(PushPopInsertAndErase) {
	std::list<int, luanics::memory::PoolAllocator<int, 2>> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.pop_front(); // remove 1
	l.erase(++l.begin()); // remove 3
	EXPECT_EQ(3, l.size());
	EXPECT_EQ(2, l.front());
	EXPECT_EQ(5, l.back());

	l.push_back(6);
	l.push_back(7);
	EXPECT_EQ(5, l.size());
	EXPECT_EQ(2, l.front());
	EXPECT_EQ(7, l.back());

}


END_TEST_SET(PoolAllocator)

}  // namespace memory
}  // namespace luanics
