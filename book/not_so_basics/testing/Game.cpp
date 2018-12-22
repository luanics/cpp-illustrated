#include "Game.hpp"
#include "Hand.hpp"

namespace luanics::cards::blackjack {

Game::Game(
	std::ostream * out,
	std::unique_ptr<Player> player,
	std::unique_ptr<Dealer> dealer
) :
	_out{out},
	_player{std::move(player)},
	_dealer{std::move(dealer)},
	_playersHand{},
	_dealersHand{}
{}

void Game::playUsing(Deck & deck) {
	// Dealer's first card is dealt face up.
	_dealersHand.clear();
	_dealersHand.add(deck.draw());
	*_out << "Dealer's Hand  : " << _dealersHand << std::endl;

	// Then Player plays.
	_playersHand.clear();
	_playersHand.add(deck.draw());
	Action playersAction = Action::HIT; // Player starts with 2 cards
	while (playersAction == Action::HIT) {
		_playersHand.add(deck.draw());
		*_out << "Player's Hand  : " << _playersHand << std::endl;
		if (_playersHand.isBust()) {
			break;
		}
		playersAction = _player->nextActionGiven(_playersHand, _dealersHand);
		*_out << "Player's Action: " << playersAction << std::endl;
	}

	// Then Dealer finishes the round.
	Action dealersAction = Action::HIT; // Dealer needs at least 2 cards
	while (dealersAction == Action::HIT) {
		_dealersHand.add(deck.draw());
		*_out << "Dealer's Hand  : " << _dealersHand << std::endl;
		if (_dealersHand.isBust()) {
			break;
		}
		dealersAction = _dealer->nextActionGiven(_dealersHand);
		*_out << "Dealers's Action: " << dealersAction << std::endl;
	}

	// Determine winner
	if (_playersHand.score() > _dealersHand.score()) {
		*_out << "Player wins!" << std::endl;
	}
	else if (_playersHand.score() < _dealersHand.score()) {
		*_out << "Dealer wins!" << std::endl;
	}
	else {
		*_out << "Tie!" << std::endl;
	}
}

} // namespace luanics::cards::blackjack
