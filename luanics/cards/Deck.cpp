#include "luanics/cards/Deck.hpp"
#include "luanics/cards/Error.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <algorithm>
#include <iostream>

namespace luanics::cards {

namespace {

std::vector<luanics::cards::Card> unshuffledCards() {
	using namespace luanics::cards;
	std::vector<Card> result;
	result.reserve(NUM_RANKS * NUM_SUITS);
	for (size_t rankIndex = 2; rankIndex < NUM_RANKS + 2; ++rankIndex) {
		Rank const rank = static_cast<Rank>(rankIndex);
		for (size_t suitIndex = 0; suitIndex < NUM_SUITS; ++suitIndex) {
			Suit const suit = static_cast<Suit>(suitIndex);
			CREATE
		}
	}
	return result;
}

}

Deck::Deck() :
	Deck(unshuffledCards())
{}

Deck::Deck(std::vector<Card> cards) :
	_randomDevice{},
	_randomGenerator{_randomDevice()},
	_cards{std::move(cards)}
{}

bool Deck::isEmpty() const {
	FIX(return false;)
}

size_t Deck::size() const {
	FIX(return 0;)
}

void Deck::shuffle() {
   std::shuffle(_cards.begin(), _cards.end(), _randomGenerator);
}

void Deck::reset() {
	_cards = unshuffledCards();
}

Card Deck::draw() {
	if (isEmpty()) {
		throw Error("draw() called on empty deck.");
	}
	CREATE
}

} // namespace luanics::cards
