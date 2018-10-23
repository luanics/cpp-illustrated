///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file ContractMacros.hpp
///
/// @brief Contract macros decorated with LUANICS_ for safety.
///
/// @see Contract.hpp
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "luanics/logging/Error.hpp"
#include "luanics/logging/Logging.hpp"

#define LUANICS_ASSERT(...) LUANICS_ASSERT_IMPL(__VA_ARGS__, "")
#define LUANICS_EXPECTS(...) LUANICS_EXPECTS_IMPL(__VA_ARGS__, "")
#define LUANICS_ENSURES(...) LUANICS_ENSURES_IMPL(__VA_ARGS__, "")

#define LUANICS_ERROR(...) LUANICS_ERROR_IMPL(__VA_ARGS__, "")
#define LUANICS_UNREACHABLE(...) LUANICS_UNREACHABLE_IMPL(__VA_ARGS__, "")

#define LUANICS_ERROR_IMPL(message, ...) \
	LUANICS_FATAL(message, __VA_ARGS__) \
	throw luanics::Error(message);

#define LUANICS_UNREACHABLE_IMPL(...) \
	LUANICS_ERROR("Should never reach this line", __VA_ARGS__)

#define LUANICS_ASSERT_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_ERROR("Failed ASSERT:" #test, __VA_ARGS__) \
	} \
}

#define LUANICS_EXPECTS_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_FATAL("Failed EXPECTS:" #test, __VA_ARGS__) \
		throw luanics::PreconditionViolation("Failed EXPECTS:" #test); \
	} \
}

#define LUANICS_ENSURES_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_FATAL("Failed ENSURES:" #test, __VA_ARGS__) \
		throw luanics::PostconditionViolation("Failed ENSURES:" #test); \
	} \
}

