#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file core/Macros.hpp
///
/// @brief Aggregates all core macros
///
/// Also removes LUANICS_ macro decoration if allowed
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/testing/core/StatementMacros.hpp"

#ifndef LUANICS_REQUIRE_MACRO_DECORATION

#define PRINT(expression) LUANICS_PRINT(expression)

#define EXPECT_EQ(expected, actual) LUANICS_EXPECT_EQ(expected, actual)
#define EXPECT_NE(expected, actual) LUANICS_EXPECT_NE(expected, actual)
#define EXPECT_LT(small, large) LUANICS_EXPECT_LT(small, large)
#define EXPECT_LE(small, large) LUANICS_EXPECT_LE(small, large)
#define EXPECT_GT(large, small) LUANICS_EXPECT_GT(large, small)
#define EXPECT_GE(large, small) LUANICS_EXPECT_GE(large, small)
#define EXPECT_NEAR(expected, actual) LUANICS_EXPECT_NEAR(expected, actual)
#define EXPECT_TRUE(expression) LUANICS_EXPECT_TRUE(expression)
#define EXPECT_FALSE(expression) LUANICS_EXPECT_FALSE(expression)
#define EXPECT_REACHED() LUANICS_EXPECT_REACHED()
#define EXPECT_NOT_REACHED() LUANICS_EXPECT_NOT_REACHED()
#define EXPECT_SAME(expected, actual) LUANICS_EXPECT_SAME(expected, actual)
#define EXPECT_THROW(expression) LUANICS_EXPECT_THROW(expression)
#define EXPECT_EXPECTS(expression) LUANICS_EXPECT_EXPECTS(expression)
#define EXPECT_ENSURES(expression) LUANICS_EXPECT_ENSURES(expression)

#define ASSERT_EQ(expected, actual) LUANICS_ASSERT_EQ(expected, actual)
#define ASSERT_NE(expected, actual) LUANICS_ASSERT_NE(expected, actual)
#define ASSERT_LT(small, large) LUANICS_ASSERT_LT(small, large)
#define ASSERT_LE(small, large) LUANICS_ASSERT_LE(small, large)
#define ASSERT_GT(large, small) LUANICS_ASSERT_GT(large, small)
#define ASSERT_GE(large, small) LUANICS_ASSERT_GE(large, small)
#define ASSERT_NEAR(expected, actual) LUANICS_ASSERT_NEAR(expected, actual)
#define ASSERT_TRUE(expression) LUANICS_ASSERT_TRUE(expression)
#define ASSERT_FALSE(expression) LUANICS_ASSERT_FALSE(expression)
#define ASSERT_AVOIDED() LUANICS_ASSERT_AVOIDED()
#define ASSERT_THROW(expression) LUANICS_ASSERT_THROW(expression)
#define ASSERT_EXPECTS(expression) LUANICS_ASSERT_EXPECTS(expression)
#define ASSERT_ENSURES(expression) LUANICS_ASSERT_ENSURES(expression)

#endif
