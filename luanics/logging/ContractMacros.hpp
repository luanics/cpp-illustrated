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
#define LUANICS_PRECONDITION(...) LUANICS_PRECONDITION_IMPL(__VA_ARGS__, "")
#define LUANICS_POSTCONDITION(...) LUANICS_POSTCONDITION_IMPL(__VA_ARGS__, "")

#define LUANICS_ERROR(...) LUANICS_ERROR_IMPL(__VA_ARGS__, "")
#define LUANICS_NEVER_REACHED(...) LUANICS_NEVER_REACHED_IMPL(__VA_ARGS__, "")

#define LUANICS_ERROR_IMPL(message, ...) \
	LUANICS_FATAL(message, __VA_ARGS__) \
	throw luanics::Error(message);

#define LUANICS_NEVER_REACHED_IMPL(...) \
	LUANICS_ERROR("Should never reach this line", __VA_ARGS__)

#define LUANICS_ASSERT_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_ERROR("Failed ASSERT:" #test, __VA_ARGS__) \
	} \
}

#define LUANICS_PRECONDITION_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_FATAL("Failed PRECONDITION:" #test, __VA_ARGS__) \
		throw luanics::PreconditionViolation("Failed PRECONDITION:" #test); \
	} \
}

#define LUANICS_POSTCONDITION_IMPL(test, ...) \
{ \
	if (!(test)) { \
		LUANICS_FATAL("Failed POSTCONDITION:" #test, __VA_ARGS__) \
		throw luanics::PostconditionViolation("Failed POSTCONDITION:" #test); \
	} \
}

