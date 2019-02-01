#pragma once

#include "luanics/profiling/GlobalNodeManager.hpp"
#include "luanics/profiling/Node.hpp"
#include "luanics/profiling/Reporter.hpp"
#include "luanics/profiling/ScopedEntrance.hpp"
#include "luanics/profiling/ScopedStart.hpp"

#ifdef LUANICS_PROFILING
	#define LUANICS_NODE_MANAGER_INSTANCE luanics::profiling::globalNodeManager()
	#define LUANICS_SCOPED_ENTRANCE_INSTANCE luanicsScopedEntranceInstance
	#define LUANICS_PROFILE_FUNCTION() \
		luanics::profiling::ScopedEntrance LUANICS_SCOPED_ENTRANCE_INSTANCE(&LUANICS_NODE_MANAGER_INSTANCE, __func__);
	#define LUANICS_PROFILE_BEGIN() \
		LUANICS_NODE_MANAGER_INSTANCE.root()->start();
	#define LUANICS_PROFILE_END() \
		LUANICS_NODE_MANAGER_INSTANCE.root()->stop();
	#define LUANICS_PROFILE_REPORT(out) \
		{ \
			luanics::profiling::reportOn(LUANICS_NODE_MANAGER_INSTANCE, &out); \
		}
#else
	#define LUANICS_PROFILE_FUNCTION()
	#define LUANICS_PROFILE_BEGIN()
	#define LUANICS_PROFILE_END()
	#define LUANICS_PROFILE_REPORT(out)
#endif
