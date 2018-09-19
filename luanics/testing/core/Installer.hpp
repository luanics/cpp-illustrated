#pragma once

#include "luanics/testing/core/Composite.hpp"

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Installer
///
/// @brief Helper class for calling add() function during dynamic initialization.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Installer {
public:
	Installer(Composite * parent, Component * child) {
		parent->add(child);
	}
};

} // namespace luanics::testing::core