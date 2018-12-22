#include "Dealer.hpp"
#include "HumanPlayer.hpp"

#include <iostream>
#include "Game.hpp"

using namespace luanics::cards::blackjack;

int main() {
	Game blackjack{
		&std::cout,
		std::make_unique<HumanPlayer>(),
		std::make_unique<Dealer>()
	};

	luanics::cards::Deck deck;
	deck.shuffle();
	blackjack.playUsing(deck);

	return 0;
}
