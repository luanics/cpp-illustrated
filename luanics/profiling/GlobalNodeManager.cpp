#include "luanics/profiling/GlobalNodeManager.hpp"

namespace luanics::profiling {

NodeManagerType & globalNodeManager() {
	static NodeManagerType instance;
	return instance;
}

} // namespace luanics::profiling
