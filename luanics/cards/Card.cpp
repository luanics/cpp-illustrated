#include "luanics/cards/Card.hpp"
#include "luanics/cards/Error.hpp"

#include <iostream>

namespace {

constexpr auto DELIMITER = "of";
}

namespace luanics {
namespace cards {

Card::Card() :
	_rank{Rank::ACE},
	_suit{Suit::SPADES}
{}

Card::Card(Rank const rank, Suit const suit) :
	_rank{rank},
	_suit{suit}
{}

Rank Card::rank() const {
	return _rank;
}

Suit Card::suit() const {
	return _suit;
}

bool Card::operator==(Card const & other) const {
	return _rank == other._rank and _suit == other._suit;
}

bool Card::operator!=(Card const & other) const {
	return not operator==(other);
}

std::ostream & operator<<(std::ostream & out, Card const & card) {
	out << card.rank() << " " << DELIMITER << " " << card.suit();
	return out;
}

std::istream & operator>>(std::istream & in, Card & card) {
	Rank rank;
	std::string delimiter;
	Suit suit;
	in >> rank >> delimiter >> suit;
	if (delimiter != DELIMITER) {
		throw Error("Invalid Card delimiter:" + delimiter);
	}
	return in;
}

}  // namespace cards
}  // namespace luanics
