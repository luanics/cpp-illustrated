#include "luanics/logging/TupleRecord.hpp"
#include "luanics/logging/SimpleSink.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstring>
#include <sstream>

using namespace luanics::logging;

BEGIN_TEST_SET(SimpleSink)

TEST(All) {
	std::ostringstream out;
	SimpleSink sink{&out};
	auto record1 = makeTupleRecord(Level::WARNING, "Source.cpp", 10, "data:", 42);
	auto record2 = makeTupleRecord(Level::INFO, "File.cpp", 200, "stuff:", 101);
	sink.consume(std::move(record1));
	sink.consume(std::move(record2));
	std::string expected{
		"[WARNING] Source.cpp:10 - data: 42 \n"
		"[INFO   ] File.cpp:200 - stuff: 101 \n"
	};
	EXPECT_EQ(expected, out.str());
}

END_TEST_SET(SimpleSink)
