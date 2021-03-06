#pragma once

#include "luanics/profiling/Macros.hpp"

#ifndef LUANICS_REQUIRE_MACRO_DECORATION

#define PROFILE_FUNCTION() LUANICS_PROFILE_FUNCTION()
#define PROFILE_BEGIN() LUANICS_PROFILE_BEGIN()
#define PROFILE_END() LUANICS_PROFILE_END()
#define PROFILE_REPORT(out) LUANICS_PROFILE_REPORT(out)

#endif
