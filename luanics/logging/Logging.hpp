///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file Logging.hpp
///
/// @brief Logging macros with LUANICS_ decoration removed for convenience.
///
/// If there is no change of macro name collision with other libraries,
///   use this file and undecorated macro names (ASSERT, etc...) for convenience.
/// Otherwise, *do not* include this file, rather include "Macros.hpp" directly
///  and use decorated macro names (LUANICS_ASSERt, etc...).
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "luanics/logging/LoggingMacros.hpp"

#ifndef LUANICS_REQUIRE_MACRO_DECORATION

#define FATAL(...) LUANICS_FATAL(__VA_ARGS__)
#define WARNING(...) LUANICS_WARNING(__VA_ARGS__)
#define INFO(...) LUANICS_INFO(__VA_ARGS__)
#define DEBUG(...) LUANICS_DEBUG(__VA_ARGS__)

#endif
