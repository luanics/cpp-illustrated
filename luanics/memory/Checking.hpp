#pragma once

#include "luanics/memory/Checker.hpp"

#ifdef LUANICS_LEAK_CHECKING

namespace luanics {
namespace leak {

extern Checker checker;

}
}

#endif
