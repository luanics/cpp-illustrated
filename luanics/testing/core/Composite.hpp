#pragma once

#include "luanics/testing/core/Component.hpp"

#include <memory>
#include <vector>

namespace luanics::testing::core {

class Reporter;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class Composite
///
/// @brief A Composite component in a test hierarchy.
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class Composite : public Component {
public:
	using ChildMapType = std::vector<Component*>;

	Composite(std::string name);

	virtual std::string const & name() const override final;
	virtual void run(Reporter & reporter) override final;

	void add(Component * child);
	ChildMapType const & children() const;

private:
	std::string _name;
	ChildMapType _children;
};

} // namespace luanics::testing::core
