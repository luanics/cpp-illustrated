#pragma once

#include "luanics/memory/Checker.hpp"

#ifdef LUANICS_LEAK_CHECKING

namespace luanics::memory {

extern Checker checker;

} // namespace luanics::memory

#endif
