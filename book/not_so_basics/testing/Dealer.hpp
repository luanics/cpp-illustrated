#pragma once

#include "Action.hpp"
#include "Hand.hpp"

namespace luanics::cards::blackjack {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Dealer
///
/// @brief Following standard rules, hits until 17 reached.
///
/// Dealer takes action based on own hand only.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Dealer {
public:
	static constexpr int minScore = 17;

	Action nextActionGiven(Hand const & dealers) {
		if (dealers.score() < minScore) {
			return Action::HIT;
		}
		else {
			return Action::STAND;
		}
	}
}; // class Dealer

} // namespace luanics::cards::blackjack
