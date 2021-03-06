#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file unit/Macros.hpp
///
/// @brief Aggregates all unit macros
///
/// Also removes LUANICS_ macro decoration if allowed
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/testing/unit/StructuralMacros.hpp"

#ifndef LUANICS_REQUIRE_MACRO_DECORATION

#define BEGIN_TEST_SET(testSetName) LUANICS_BEGIN_TEST_SET(testSetName)
#define END_TEST_SET(testSetName) LUANICS_END_TEST_SET()

#define TEST(testName) LUANICS_TEST(testName)

#endif
