#pragma once

#include "luanics/profiling/NodeManager.hpp"

namespace luanics::profiling {

// Change template parameters to customize...
using NodeManagerType = NodeManager<>;

NodeManagerType & globalNodeManager();

} // namespace luanics::profiling
