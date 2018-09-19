#pragma once

#include "luanics/testing/unit/Reporter.hpp"

#include <memory>

namespace luanics {

namespace string { class Matcher;}

namespace testing::unit {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Filter
///
/// @brief Ad-hoc Decorator for Reporter that filters out matching tests.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Filter : public Reporter {
public:
	Filter(
		std::unique_ptr<string::Matcher> testSetMatcher,
		std::unique_ptr<string::Matcher> testMatcher,
		Reporter * filtered
	);

	virtual bool startTestSuite() override final;
	virtual void finishTestSuite(core::Outcome const outcome) override final;

	virtual bool startTestSet(std::string const & name) override final;
	virtual void finishTestSet(std::string const & name, core::Outcome const outcome) override final;

	virtual bool startTest(std::string const & name) override final;
	virtual void finishTest(std::string const & name, core::Outcome const outcome) override final;

	virtual void report(core::Error const & error) override final;
	virtual void report(core::Log const & log) override final;
	virtual void report(core::Result const & result) override final;

private:
	std::unique_ptr<string::Matcher> _testSetMatcher;
	std::unique_ptr<string::Matcher> _testMatcher;
	Reporter * _filtered;
}; // class Filter

} // namespace testing::unit
} // namespace luanics
