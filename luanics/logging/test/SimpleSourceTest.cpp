#include "luanics/logging/LevelFilter.hpp"
#include "luanics/logging/SimpleSink.hpp"
#include "luanics/logging/SimpleSource.hpp"
#include "luanics/logging/TupleRecord.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstring>
#include <sstream>

using namespace luanics::logging;

BEGIN_TEST_SET(SimpleSource)

TEST(All) {
	std::ostringstream out;
	SimpleSource source;
	source.setFilter(std::make_unique<LevelFilter>(Level::INFO));
	source.setSink(std::make_unique<SimpleSink>(&out));
	auto record1 = makeTupleRecord(Level::WARNING, "Source.cpp", 10, "data:", 42);
	auto record2 = makeTupleRecord(Level::INFO, "File.cpp", 200, "stuff:", 101);
	auto record3 = makeTupleRecord(Level::DEBUG, "File.cpp", 300, "stuff:", 201);
	source.submit(std::move(record1));
	source.submit(std::move(record2));
	source.submit(std::move(record3));
	std::string expected{
		"[WARNING] Source.cpp:10 - data: 42 \n"
		"[INFO   ] File.cpp:200 - stuff: 101 \n"
	};
	EXPECT_EQ(expected, out.str());
}

END_TEST_SET(SimpleSource)
