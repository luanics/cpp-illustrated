#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file core/StatementMacros.hpp
///
/// @brief Test statement macros shared across testing framework.
///
/// Note that all names are decorated (minimally) with "LUANICS_" prefix to avoid name clashes.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/string/Conversion.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"

#include <cmath>

//*********************************************************
// Definitions
//*********************************************************

#define LUANICS_DOUBLE_COMPARISON_PRECISION 1e-6

//*********************************************************
// Messages
//*********************************************************

#define LUANICS_PRINT(expression) \
	LUANICS_REPORTER.report(luanics::testing::core::Log{__FILE__, __LINE__, #expression " = " + luanics::string::toString((expression))});

#define LUANICS_EXPECT_EQ_EXPRESSION(expectedString, actualString)\
	expectedString "==" actualString

#define LUANICS_EXPECT_EQ_MESSAGE(expectedString, expectedValue, actualString, actualValue)\
	std::string("in expression ") + LUANICS_EXPECT_EQ_EXPRESSION(expectedString, actualString) + ", expected=" + luanics::string::stringify(expectedValue) + " but actual=" + luanics::string::stringify(actualValue)

#define LUANICS_EXPECT_LT_EXPRESSION(smallString, largeString)\
	smallString "<" largeString

#define LUANICS_EXPECT_LT_MESSAGE(smallString, smallValue, largeString, largeValue)\
	std::string("in expression ") + LUANICS_EXPECT_LT_EXPRESSION(smallString, largeString) + ", " + luanics::string::stringify(smallValue) + " is not less than " + luanics::string::stringify(largeValue)

#define LUANICS_EXPECT_LE_EXPRESSION(smallString, largeString)\
	smallString "<=" largeString

#define LUANICS_EXPECT_LE_MESSAGE(smallString, smallValue, largeString, largeValue)\
	std::string("in expression ") + LUANICS_EXPECT_LE_EXPRESSION(smallString, largeString) + ", " + luanics::string::stringify(smallValue) + " is not less than or equal to " + luanics::string::stringify(largeValue)

#define LUANICS_EXPECT_GT_EXPRESSION(largeString, smallString)\
	largeString ">" smallString

#define LUANICS_EXPECT_GT_MESSAGE(largeString, largeValue, smallString, smallValue)\
	std::string("in expression ") + LUANICS_EXPECT_GT_EXPRESSION(largeString, smallString) + ", " + luanics::string::stringify(largeValue) + " is not greater than " + luanics::string::stringify(smallValue)

#define LUANICS_EXPECT_GE_EXPRESSION(largeString, smallString)\
	largeString ">=" smallString

#define LUANICS_EXPECT_GE_MESSAGE(largeString, largeValue, smallString, smallValue)\
	std::string("in expression ") + LUANICS_EXPECT_GE_EXPRESSION(largeString, smallString) + ", " + luanics::string::stringify(largeValue) + " is not greater than or equal to " + luanics::string::stringify(smallValue)

#define LUANICS_EXPECT_REACHED_MESSAGE()\
	"reached REACHED section"

#define LUANICS_EXPECT_NOT_REACHED_MESSAGE()\
	"reached NOT_REACHED section"

#define LUANICS_EXPECT_SAME_MESSAGE(expectedString, actualString)\
	std::string("expected ") + expectedString + std::string(" to be have same type as ") + actualString

#define LUANICS_EXPECT_THROW_MESSAGE(expressionString)\
	std::string("in expression ") + expressionString + std::string(" expected throw")

#define LUANICS_EXPECT_NO_THROW_MESSAGE(expressionString)\
	std::string("in expression ") + expressionString + std::string(" expected throw")

#define LUANICS_EXPECT_EXPECTS_MESSAGE(expressionString)\
	std::string("in expression ") + expressionString + std::string(" expected precondition violation")

#define LUANICS_EXPECT_ENSURES_MESSAGE(expressionString)\
	std::string("in expression ") + expressionString + std::string(" expected postcondition violation")

//*********************************************************
// Bodies
//*********************************************************

#define LUANICS_EXPECT_EQ_BODY(expected, actual) \
	auto const expectedValue = ((expected)); \
	auto const actualValue = ((actual)); \
	bool const isPassing = expectedValue == actualValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EQ_MESSAGE(#expected, expectedValue, #actual, actualValue)});

#define LUANICS_EXPECT_NE_BODY(expected, actual) \
	auto const expectedValue = ((expected)); \
	auto const actualValue = ((actual)); \
	bool const isPassing = expectedValue != actualValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EQ_MESSAGE(#expected, expectedValue, #actual, actualValue)});

#define LUANICS_EXPECT_LT_BODY(small, large) \
	auto const smallValue = ((small)); \
	auto const largeValue = ((large)); \
	bool const isPassing = smallValue < largeValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_LT_MESSAGE(#small, smallValue, #large, largeValue)});
//	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, "hi dad"});

#define LUANICS_EXPECT_LE_BODY(small, large) \
	auto const smallValue = ((small)); \
	auto const largeValue = ((large)); \
	bool const isPassing = smallValue <= largeValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_LE_MESSAGE(#small, smallValue, #large, largeValue)});

#define LUANICS_EXPECT_GT_BODY(large, small) \
	auto const smallValue = ((small)); \
	auto const largeValue = ((large)); \
	bool const isPassing = largeValue > smallValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_GT_MESSAGE(#large, largeValue, #small, smallValue)});

#define LUANICS_EXPECT_GE_BODY(large, small) \
	auto const smallValue = ((small)); \
	auto const largeValue = ((large)); \
	bool const isPassing = largeValue >= smallValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_GE_MESSAGE(#large, largeValue, #small, smallValue)});

#define LUANICS_EXPECT_NEAR_BODY(expected, actual) \
	auto const expectedValue = ((expected)); \
	auto const actualValue = ((actual)); \
	bool const isPassing = std::fabs(expectedValue - actualValue) < LUANICS_DOUBLE_COMPARISON_PRECISION; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EQ_MESSAGE(#expected, expectedValue, #actual, actualValue)});

#define LUANICS_EXPECT_TRUE_BODY(actual) \
	auto const actualValue = (actual); \
	bool const isPassing = actualValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EQ_MESSAGE("true", true, #actual, actualValue)});

#define LUANICS_EXPECT_FALSE_BODY(actual) \
	auto const actualValue = (actual); \
	bool const isPassing = !actualValue; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EQ_MESSAGE("false", false, #actual, actualValue)});

#define LUANICS_EXPECT_REACHED_BODY() \
	bool const isPassing = true; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_REACHED_MESSAGE()});

#define LUANICS_EXPECT_NOT_REACHED_BODY() \
	bool const isPassing = false; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_NOT_REACHED_MESSAGE()});

#define LUANICS_EXPECT_SAME_BODY(expected, actual) \
	bool const isPassing = std::is_same_v<expected, actual>; \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_SAME_MESSAGE(#expected, #actual)});

#define LUANICS_EXPECT_THROW_BODY(expression) \
	bool isPassing = false; \
	try { \
		(expression); \
	} \
	catch (...) { \
		isPassing = true; \
	} \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_THROW_MESSAGE(#expression)});

#define LUANICS_EXPECT_NO_THROW_BODY(expression) \
	bool isPassing = true; \
	try { \
		(expression); \
	} \
	catch (...) { \
		isPassing = false; \
	} \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_NO_THROW_MESSAGE(#expression)});

#define LUANICS_EXPECT_EXPECTS_BODY(expression) \
	bool isPassing = false; \
	try { \
		(expression); \
	} \
	catch (luanics::PreconditionViolation const & e) { \
		isPassing = true; \
	} \
	catch (...) {} \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_EXPECTS_MESSAGE(#expression)});

#define LUANICS_EXPECT_ENSURES_BODY(expression) \
	bool isPassing = false; \
	try { \
		(expression); \
	} \
	catch (luanics::PostconditionViolation const & e) { \
		isPassing = true; \
	} \
	catch (...) {} \
	LUANICS_REPORTER.report(luanics::testing::core::Result{isPassing, __FILE__, __LINE__, LUANICS_EXPECT_ENSURES_MESSAGE(#expression)});

//*********************************************************
// EXPECT macros
//*********************************************************

#define LUANICS_EXPECT_EQ(expected, actual) \
	{ \
		LUANICS_EXPECT_EQ_BODY(expected, actual) \
	}

#define LUANICS_EXPECT_NE(expected, actual) \
	{ \
		LUANICS_EXPECT_NE_BODY(expected, actual) \
	}

#define LUANICS_EXPECT_LT(small, large) \
	{ \
		LUANICS_EXPECT_LT_BODY(small, large) \
	}

#define LUANICS_EXPECT_LE(small, large) \
	{ \
		LUANICS_EXPECT_LE_BODY(small, large) \
	}

#define LUANICS_EXPECT_GT(large, small) \
	{ \
		LUANICS_EXPECT_GT_BODY(large, small) \
	}

#define LUANICS_EXPECT_GE(large, small) \
	{ \
		LUANICS_EXPECT_GE_BODY(large, small) \
	}

#define LUANICS_EXPECT_NEAR(expected, actual) \
	{ \
		LUANICS_EXPECT_NEAR_BODY(expected, actual) \
	}

#define LUANICS_EXPECT_TRUE(actual) \
	{ \
		LUANICS_EXPECT_TRUE_BODY(actual) \
	}

#define LUANICS_EXPECT_FALSE(actual) \
	{ \
		LUANICS_EXPECT_FALSE_BODY(actual) \
	}

#define LUANICS_EXPECT_REACHED() \
	{ \
		LUANICS_EXPECT_REACHED_BODY() \
	}

#define LUANICS_EXPECT_NOT_REACHED() \
	{ \
		LUANICS_EXPECT_NOT_REACHED_BODY() \
	}

#define LUANICS_EXPECT_THROW(expression) \
	{ \
		LUANICS_EXPECT_THROW_BODY(expression) \
	}

#define LUANICS_EXPECT_NO_THROW(expression) \
	{ \
		LUANICS_EXPECT_NO_THROW_BODY(expression) \
	}

#define LUANICS_EXPECT_EXPECTS(expression) \
	{ \
		LUANICS_EXPECT_EXPECTS_BODY(expression) \
	}

//*********************************************************
// ASSERT macros
//*********************************************************

#define LUANICS_ASSERT_EQ(expected, actual) \
	{ \
		LUANICS_EXPECT_EQ_BODY(expected, actual) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_NE(expected, actual) \
	{ \
		LUANICS_EXPECT_NE_BODY(expected, actual) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_LT(small, large) \
	{ \
		LUANICS_EXPECT_LT_BODY(small, large) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_LE(small, large) \
	{ \
		LUANICS_EXPECT_LE_BODY(small, large) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_GT(large, small) \
	{ \
		LUANICS_EXPECT_GT_BODY(large, small) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_GE(large, small) \
	{ \
		LUANICS_EXPECT_GE_BODY(large, small) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_NEAR(expected, actual) \
	{ \
		LUANICS_ASSERT_NEAR_BODY(expected, actual) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_TRUE(actual) \
	{ \
		LUANICS_EXPECT_TRUE_BODY(actual) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_FALSE(actual) \
	{ \
		LUANICS_EXPECT_FALSE_BODY(actual) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_NOT_REACHED() \
	{ \
		LUANICS_EXPECT_NOT_REACHED_BODY() \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_THROW(expression) \
	{ \
		LUANICS_EXPECT_THROW_BODY(expression) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_NO_THROW(expression) \
	{ \
		LUANICS_EXPECT_NO_THROW_BODY(expression) \
		if (not isPassing) return; \
	}

#define LUANICS_ASSERT_EXPECTS(expression) \
	{ \
		LUANICS_EXPECT_EXPECTS_BODY(expression) \
		if (not isPassing) return; \
	}
