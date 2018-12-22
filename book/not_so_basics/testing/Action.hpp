#pragma once

#include <iostream>

namespace luanics::cards::blackjack {

enum class Action {
	HIT,  ///< Draw another card
	STAND ///< Do not draw another card
};

inline std::ostream & operator<<(std::ostream & out, Action const action) {
	switch (action) {
		case Action::HIT: out << "HIT"; break;
		case Action::STAND: out << "STAND"; break;
	}
	return out;
}

} // namespace luanics::cards::blackjack
