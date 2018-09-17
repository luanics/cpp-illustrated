#include "luanics/logging/Logger.hpp"
#include "luanics/logging/TupleRecord.hpp"

#include <iostream>

#ifdef LUANICS_LOGGING
	#define LUANICS_LOG(level, ...) \
		luanics::logging::logger().submit(luanics::logging::makeTupleRecord(level, __FILE__, __LINE__, __VA_ARGS__));
#else
	#define LUANICS_LOG(level, ...)
#endif

#define LUANICS_FATAL(...) LUANICS_LOG(luanics::logging::Level::FATAL, __VA_ARGS__)
#define LUANICS_WARNING(...) LUANICS_LOG(luanics::logging::Level::WARNING, __VA_ARGS__)
#define LUANICS_INFO(...) LUANICS_LOG(luanics::logging::Level::INFO, __VA_ARGS__)
#define LUANICS_DEBUG(...) LUANICS_LOG(luanics::logging::Level::DEBUG, __VA_ARGS__)
#define LUANICS_TRACE(...) LUANICS_LOG(luanics::logging::Level::TRACE, __VA_ARGS__)
