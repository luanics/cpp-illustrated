#pragma once

#include "Action.hpp"
#include "Hand.hpp"

namespace luanics::cards::blackjack {

/////////////////////////////////////////////////////////////////////
//////////////////////////d///////////////////////////////////////////
///
/// @class Player
///
/// @brief Provides Action for player based on player and dealer hands.
///
/// Players take action knowing 1 (or maybe 2) of dealer's cards.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Player {
public:
	virtual Action nextActionGiven(Hand const & player, Hand const & dealer) = 0;

	virtual ~Player() = default;
}; // class Player

} // namespace luanics::cards::blackjack
