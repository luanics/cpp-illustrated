#include "luanics/cards/Suit.hpp"
#include "luanics/cards/Error.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <iostream>
#include <string>

namespace {

constexpr auto CLUBS_STRING = "CLUBS";
constexpr auto DIAMONDS_STRING = "DIAMONDS";
constexpr auto HEARTS_STRING = "HEARTS";
constexpr auto SPADES_STRING = "SPADES";

}

namespace luanics {
namespace cards {

//*****************************************************************************
// Queries
//*****************************************************************************

bool isBlack(Suit const & suit) {
	FIX(return suit == Suit::CLUBS or suit == Suit::SPADES;)
}

bool isRed(Suit const & suit) {
	FIX(return not isBlack(suit));
}

//*****************************************************************************
// IO
//*****************************************************************************

std::ostream & operator<<(std::ostream & out, Suit const & suit) {
	// See Rank.cpp for an example
	CREATE ANSWER(
	switch (suit) {
		case Suit::CLUBS: out << CLUBS_STRING; break;
		case Suit::DIAMONDS: out << DIAMONDS_STRING; break;
		case Suit::HEARTS: out << HEARTS_STRING; break;
		case Suit::SPADES: out << SPADES_STRING; break;
		default: throw Error{"Invalid Rank value:" + std::to_string(static_cast<uint8_t>(suit))};
	}
	)
	return out;
}

std::istream & operator>>(std::istream & in, Suit & suit) {
	// See Rank.cpp for an example
	CREATE ANSWER(
	std::string s;
	in >> s;
	if (s == CLUBS_STRING) suit = Suit::CLUBS;
	else if (s == DIAMONDS_STRING) suit = Suit::DIAMONDS;
	else if (s == HEARTS_STRING) suit = Suit::HEARTS;
	else if (s == SPADES_STRING) suit = Suit::SPADES;
	else throw Error{"Invalid Suit string:" + s};
	)
	return in;
}

}  // namespace cards
}  // namespace luanics
