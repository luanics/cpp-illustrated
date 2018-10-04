#pragma once

#include "luanics/testing/core/Component.hpp"

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class DummyComponent
///
/// @brief Component test double that simply provides a name.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class DummyComponent final : public Component {
public:
	DummyComponent(std::string name) : _name{std::move(name)} {}
	virtual std::string const & name() const {return _name;}
	virtual void run(Reporter & reporter) {}

private:
	std::string _name;
}; // class DummyComponent

} // namespace luanics::testing::core
