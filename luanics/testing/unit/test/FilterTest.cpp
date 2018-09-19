#include "luanics/string/EnumeratedMatcher.hpp"
#include "luanics/testing/Unit.hpp"
#include "luanics/testing/unit/Filter.hpp"
#include "luanics/testing/unit/test/SpyReporter.hpp"

namespace luanics::testing::unit {

BEGIN_TEST_SET(Filter)

TEST(All) {
	SpyReporter reporter{};
	Filter filter{
		std::make_unique<string::EnumeratedMatcher>(std::vector<std::string>{"Cat", "Dog"}),
		std::make_unique<string::EnumeratedMatcher>(std::vector<std::string>{"Black", "White"}),
		&reporter
	};

	EXPECT_EQ(0, reporter.numStartTestSuiteCalls());
	filter.startTestSuite();
	EXPECT_EQ(1, reporter.numStartTestSuiteCalls());

	bool const isStartingFishTestSet = filter.startTestSet("Fish");
	EXPECT_FALSE(isStartingFishTestSet);
	EXPECT_EQ(0, reporter.startTestSetCalls().size());

	bool const isStartingDogTestSet = filter.startTestSet("Dog");
	EXPECT_TRUE(isStartingDogTestSet);
	EXPECT_EQ(1, reporter.startTestSetCalls().size());

	bool const isStartingGreenTest = filter.startTest("Green");
	EXPECT_FALSE(isStartingGreenTest);
	EXPECT_EQ(0, reporter.startTestCalls().size());

	bool const isStartingBlackTest = filter.startTest("Black");
	EXPECT_TRUE(isStartingBlackTest);
	EXPECT_EQ(1, reporter.startTestCalls().size());

	EXPECT_EQ(0, reporter.reportResultCalls().size());
	filter.report(core::Result{false, "", 0, ""});
	EXPECT_EQ(1, reporter.reportResultCalls().size());

	EXPECT_EQ(0, reporter.finishTestSetCalls().size());
	filter.finishTestSet("Dog", core::Outcome::FAIL);
	EXPECT_EQ(1, reporter.finishTestSetCalls().size());

	EXPECT_EQ(0, reporter.finishTestSuiteCalls().size());
	filter.finishTestSuite(core::Outcome::FAIL);
	EXPECT_EQ(1, reporter.finishTestSuiteCalls().size());
}

END_TEST_SET(Filter)

} // namespace luanics::testing::unit
