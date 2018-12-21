#pragma once

#include "luanics/cards/Rank.hpp"
#include "luanics/cards/Suit.hpp"

#include <iosfwd>

namespace luanics::cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Card
///
/// @brief A single playing card in a standard deck of cards.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Card {
public:
	Card(); ///< ACE of SPADES
	Card(Rank const rank, Suit const suit);

	Rank rank() const;
	Suit suit() const;

	bool operator==(Card const & other) const;
	bool operator!=(Card const & other) const;

private:
	Rank _rank;
	Suit _suit;
}; // class Card

/// Prints "<rank> of <suit>", e.g., "ACE of SPADES"
std::ostream & operator<<(std::ostream & out, Card const & card);
std::istream & operator>>(std::istream & in, Card & card);

} // namespace luanics::cards
