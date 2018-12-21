#pragma once

#include <functional>
#include <iostream>

namespace luanics {
namespace cards {
	class Model;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Controller
///
/// @brief Tells us what actions the player has chosen.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Controller {
public:
	using ActionType = std::function<void(Model &)>;

	Controller(std::istream * in, Model const & model);

	/// @returns invalid ActionType if invalid input.
	ActionType nextAction();

private:
	std::istream * _in;
}; // class Controller

}  // namespace cards
}  // namespace luanics
