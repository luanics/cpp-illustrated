#pragma once

#include "Dealer.hpp"
#include "Player.hpp"

#include <luanics/cards/Card.hpp>
#include <luanics/cards/Deck.hpp>

#include <memory>

namespace luanics::cards::blackjack {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Game
///
/// @brief The Blackjack card game.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Game {
public:
	Game(
		std::ostream * out,
		std::unique_ptr<Player> player,
		std::unique_ptr<Dealer> dealer
	);

	void playUsing(Deck & deck);
	Hand const & playersHand() const;
	Hand const & dealersHand() const;

private:
	std::ostream * _out;
	std::unique_ptr<Player> _player;
	std::unique_ptr<Dealer> _dealer;
	Hand _playersHand;
	Hand _dealersHand;
}; // class Game

} // namespace luanics::cards::blackjack
