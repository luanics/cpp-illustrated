#include "luanics/testing/Unit.hpp"
#include "luanics/testing/core/SimpleReporter.hpp"

namespace luanics::testing::core {

BEGIN_TEST_SET(TestLeaf)

TEST(Install) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	EXPECT_EQ(0, testSuite.children().size());
	EXPECT_EQ(0, testCase.children().size());

	Installer testCaseInstaller(testSuite, testCase);
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(0, testCase.children().size());
}

class PassingTest : public Leaf {
public:
	PassingTest() : Leaf{"Passing"} {}
private:
	void doRun(Reporter & reporter) {
		reporter.report(Result{true, __FILE__, __LINE__, "passing"});
	}
};

TEST(Pass) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	Installer testCaseInstaller(testSuite, testCase);
	PassingTest passingTest;
	Installer testInstaller(testCase, passingTest);
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(1, testCase.children().size());

	SimpleReporter reporter;
	testSuite.run(reporter);
	EXPECT_EQ(1, reporter.numPassResults());
	EXPECT_EQ(0, reporter.numFailResults());
	EXPECT_EQ(0, reporter.numErrors());
	EXPECT_EQ(0, reporter.numLogs());
}

class FailingTest : public Leaf {
public:
	FailingTest() : Leaf{"Failing"} {}
private:
	void doRun(Reporter & reporter) {
		reporter.report(Result{false, __FILE__, __LINE__, "failing"});
	}
};

TEST(Fail) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	Installer testCaseInstaller{testSuite, testCase};
	FailingTest failingTest;
	Installer testInstaller{testCase, failingTest};
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(1, testCase.children().size());

	SimpleReporter reporter;
	testSuite.run(reporter);
	EXPECT_EQ(0, reporter.numPassResults());
	EXPECT_EQ(1, reporter.numFailResults());
	EXPECT_EQ(0, reporter.numErrors());
	EXPECT_EQ(0, reporter.numLogs());
}

class ErringTest : public Leaf {
public:
	ErringTest() : Leaf{"Erring"} {}
private:
	void doRun(Reporter & reporter) {
		throw std::runtime_error("error");
	}
};

TEST(Error) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	Installer testCaseInstaller{testSuite, testCase};
	ErringTest erringTest;
	Installer testInstaller{testCase, erringTest};
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(1, testCase.children().size());

	SimpleReporter reporter;
	testSuite.run(reporter);
	EXPECT_EQ(0, reporter.numPassResults());
	EXPECT_EQ(0, reporter.numFailResults());
	EXPECT_EQ(1, reporter.numErrors());
	EXPECT_EQ(0, reporter.numLogs());
}

class LoggingTest : public Leaf {
public:
	LoggingTest() : Leaf{"Logging"} {}
private:
	void doRun(Reporter & reporter) {
		reporter.report(Log{__FILE__, __LINE__, "logging"});
	}
};

TEST(Log) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	Installer testCaseInstaller{testSuite, testCase};
	LoggingTest loggingTest;
	Installer testInstaller{testCase, loggingTest};
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(1, testCase.children().size());

	SimpleReporter reporter;
	testSuite.run(reporter);
	EXPECT_EQ(0, reporter.numPassResults());
	EXPECT_EQ(0, reporter.numFailResults());
	EXPECT_EQ(0, reporter.numErrors());
	EXPECT_EQ(1, reporter.numLogs());
}

TEST(All) {
	Composite testSuite{"TestSuite"};
	Composite testCase{"TestCase"};
	Installer testCaseInstaller{testSuite, testCase};
	PassingTest passingTest;
	Installer passingTestInstaller{testCase, passingTest};
	FailingTest failingTest;
	Installer failingTestInstaller{testCase, failingTest};
	ErringTest erringTest;
	Installer erringTestInstaller{testCase, erringTest};
	LoggingTest loggingTest;
	Installer loggingTestInstaller{testCase, loggingTest};
	EXPECT_EQ(1, testSuite.children().size());
	EXPECT_EQ(4, testCase.children().size());

	SimpleReporter reporter;
	testSuite.run(reporter);
	EXPECT_EQ(1, reporter.numPassResults());
	EXPECT_EQ(1, reporter.numFailResults());
	EXPECT_EQ(1, reporter.numErrors());
	EXPECT_EQ(1, reporter.numLogs());
}

END_TEST_SET()

} // namespace luanics::testing::core
