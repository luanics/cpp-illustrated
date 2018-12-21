#include "luanics/cards/Deck.hpp"
#include "luanics/cards/Error.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <algorithm>
#include <iostream>

namespace luanics {
namespace cards {

namespace {

std::vector<luanics::cards::Card> unshuffledCards() {
	using namespace luanics::cards;
	std::vector<Card> result;
	result.reserve(NUM_RANKS * NUM_SUITS);
	for (size_t rankIndex = 2; rankIndex < NUM_RANKS + 2; ++rankIndex) {
		Rank const rank = static_cast<Rank>(rankIndex);
		for (size_t suitIndex = 0; suitIndex < NUM_SUITS; ++suitIndex) {
			Suit const suit = static_cast<Suit>(suitIndex);
			CREATE ANSWER(result.push_back(Card(rank, suit));)
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
	FIX(RIGHT(return size() == 0;)WRONG(return false;))
}

size_t Deck::size() const {
	FIX(RIGHT(return _cards.size();)WRONG(return 0;))
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
	CREATE ANSWER(
	Card result = _cards.back();
	_cards.pop_back();
	return result;
	)
}

}  // namespace cards
}  // namespace luanics
