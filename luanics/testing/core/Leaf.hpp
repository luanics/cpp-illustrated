#pragma once

#include "luanics/testing/core/Component.hpp"

#include <list>

namespace luanics::testing::core {

class Reporter;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///
/// @class Leaf
///
/// @brief A leaf in a testing hierarchy.
///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class Leaf : public Component {
public:
	Leaf(std::string name);

	virtual std::string const & name() const override final;
	virtual void run(Reporter & reporter) override final;

private:
	virtual void doRun(Reporter & reporter) = 0;

	std::string _name;
};

} // namespace luanics::testing::core
