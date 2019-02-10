#pragma once

#include "luanics/cards/Card.hpp"

#include <iosfwd>
#include <random>
#include <vector>

namespace luanics::cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Deck
///
/// @brief A standard (face-down) deck of cards.
///
/// The Desk is "face-down" in that you can't peek at the top card, you can
///  only "draw()" it to see what it is.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Deck {
public:
	/// Constructs an ordered, 52-card deck.
	/// Order is TWO of CLUBS, TWO of DIAMONDS, ..., up to ACE of SPADES,
	///  with ACE of SPADES as the first draw card.
	Deck();
	/// Copies the Cards without shuffling
	Deck(std::vector<Card> cards);

	bool isEmpty() const;
	size_t size() const;

	void shuffle();
	void reset(); ///< Reset to unshuffled deck.
	Card draw(); ///< Draw top card

private:
	std::random_device _randomDevice;
	std::mt19937 _randomGenerator;
	std::vector<Card> _cards;
}; // class Deck

} // namespace luanics::cards
