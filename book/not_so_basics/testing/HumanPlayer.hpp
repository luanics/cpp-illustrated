#pragma once

#include "Player.hpp"

namespace luanics::cards::blackjack {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class HumanPlayer
///
/// @brief Player controlled by input from console.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class HumanPlayer : public Player {
public:
	virtual Action nextActionGiven(Hand const & players, Hand const & dealers) override final {
		bool isValidAction = false;
		do {
			std::cout << "Enter Action (HIT, STAND): ";
			std::string choice;
			std::cin >> choice;
			if (choice == "HIT") {
				return Action::HIT;
			}
			else if (choice == "STAND") {
				return Action::STAND;
			}
			else {
				isValidAction = false;
			}
		}
		while (not isValidAction);
	}
}; // class HumanPlayer

} // namespace luanics::cards::blackjack
