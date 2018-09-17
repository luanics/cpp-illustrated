#pragma once

#include "luanics/testing/core/Composite.hpp"

namespace luanics::testing::tutorial {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class CompositeReference
///
/// @brief Helper that holds a link to a Component and installs Composites.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class CompositeReference {
public:
	CompositeReference(core::Composite * composite) : _composite{composite} {}
	void install(core::Component * component) {_composite->add(component);}

private:
	core::Composite * _composite;
}; // class CompositeReference

} // namespace luanics::testing::tutorial
