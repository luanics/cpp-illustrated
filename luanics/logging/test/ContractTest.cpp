#include "luanics/logging/Contract.hpp"
#include "luanics/logging/Logger.hpp"
#include "luanics/logging/SimpleSink.hpp"
#include "luanics/logging/SimpleSource.hpp"
#include "luanics/testing/Unit.hpp"

#include <cstring>
#include <sstream>

using namespace luanics::logging;

BEGIN_TEST_SET(Contract)

TEST(All) {
	bool isExceptionThrown = false;
	try {
		LUANICS_PRECONDITION(false);
	}
	catch (luanics::Error const & error) {
		isExceptionThrown = true;
	}
	EXPECT_TRUE(isExceptionThrown);
}

END_TEST_SET(Contract)
