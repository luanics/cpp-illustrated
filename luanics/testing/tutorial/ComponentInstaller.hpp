#pragma once

#include "luanics/testing/core/Composite.hpp"
#include "luanics/testing/tutorial/CompositeReference.hpp"

namespace luanics::testing::tutorial {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class ComponentInstaller
///
/// @brief Helper to call install() method during dynamic initialization.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class ComponentInstaller {
public:
	ComponentInstaller(CompositeReference * composite, core::Component * component) {
		composite->install(component);
	}
}; // class ComponentInstaller

} // namespace luanics::testing::tutorial
