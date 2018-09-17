#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file tutorial/Macros.hpp
///
/// @brief Aggregates all tutorial macros
///
/// Also removes LUANICS_ macro decoration if allowed
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/testing/tutorial/AnswerMacros.hpp"
#include "luanics/testing/tutorial/PlaceholderMacros.hpp"
#include "luanics/testing/tutorial/StructuralMacros.hpp"

#ifndef LUANICS_REQUIRE_MACRO_DECORATION

#define BEGIN_CHAPTER(name) LUANICS_BEGIN_CHAPTER(name)
#define END_CHAPTER(name) LUANICS_END_CHAPTER(name)
#define SECTION(name) LUANICS_SECTION(name)

#define BEGIN_SUBPROJECT(name) LUANICS_BEGIN_SUBPROJECT(name)
#define END_SUBPROJECT(name) LUANICS_END_SUBPROJECT(name)
#define SUBPROJECT_TEST(name) LUANICS_SUBPROJECT_TEST(name)

#define FIX(x) LUANICS_FIX(x)
#define CREATE LUANICS_CREATE

#define ANSWER(...) LUANICS_ANSWER(__VA_ARGS__)
#define RIGHT(x) LUANICS_RIGHT(x)
#define WRONG(x) LUANICS_WRONG(x)

#endif
