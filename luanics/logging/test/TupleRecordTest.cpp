#include "luanics/logging/TupleRecord.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstring>
#include <sstream>

using namespace luanics::logging;

BEGIN_TEST_SET(TupleRecord)

TEST(Construct) {
	auto record = makeTupleRecord(Level::WARNING, "Source.cpp", 10, "data:", 42);
	EXPECT_EQ(Level::WARNING, record->level());
	EXPECT_EQ(0, std::strcmp("Source.cpp", record->file()));
	EXPECT_EQ(10, record->line());
}

TEST(WriteMessage) {
	auto record = makeTupleRecord(Level::WARNING, "Source.cpp", 10, "data:", 42);
	std::ostringstream out;
	record->writeMessageTo(out);
	EXPECT_EQ("data: 42 ", out.str());
}

END_TEST_SET(TupleRecord)
