#include "luanics/testing/core/test/DummyComponent.hpp"
#include "luanics/testing/core/test/SpyAugmentedReporter.hpp"
#include "luanics/testing/core/StringExcluderDecorator.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::testing::core {

BEGIN_TEST_SET(StringExcluderDecorator)

enum Level {
	TEST_SUITE = 0,
	TEST_SET = 1,
	TEST = 2
};

TEST(All) {
	SpyAugmentedReporter reporter{};

	StringExcluderDecorator filter{&reporter, "_Tutorial"};

	EXPECT_EQ(0, reporter.startReportCalls().size());
	filter.startReportOn(DummyComponent{"Suite"}, TEST_SUITE);
	EXPECT_EQ(1, reporter.startReportCalls().size());

	bool const isStartingFishTestSet = filter.startReportOn(DummyComponent{"Fish_Tutorial"}, TEST_SET);
	EXPECT_FALSE(isStartingFishTestSet);
	EXPECT_EQ(1, reporter.startReportCalls().size());

	bool const isStartingDogTestSet = filter.startReportOn(DummyComponent{"Dog"}, TEST_SET);
	EXPECT_TRUE(isStartingDogTestSet);
	EXPECT_EQ(2, reporter.startReportCalls().size());

	bool const isStartingGreenTest = filter.startReportOn(DummyComponent{"Green_Tutorial"}, TEST);
	EXPECT_FALSE(isStartingGreenTest);
	EXPECT_EQ(2, reporter.startReportCalls().size());

	bool const isStartingBlackTest = filter.startReportOn(DummyComponent{"Black"}, TEST);
	EXPECT_TRUE(isStartingBlackTest);
	EXPECT_EQ(3, reporter.startReportCalls().size());

	EXPECT_EQ(0, reporter.reportResultCalls().size());
	filter.report(core::Result{false, "", 0, ""});
	EXPECT_EQ(1, reporter.reportResultCalls().size());

	EXPECT_EQ(0, reporter.finishReportCalls().size());
	filter.finishReportOn(DummyComponent{"Dog"}, TEST_SET, Outcome::FAIL);
	EXPECT_EQ(1, reporter.finishReportCalls().size());

	filter.finishReportOn(DummyComponent{"Suite"}, TEST_SUITE, Outcome::FAIL);
	EXPECT_EQ(2, reporter.finishReportCalls().size());
}

END_TEST_SET(StringExcluderDecorator)

} // namespace luanics::testing::unit
