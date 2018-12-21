#include "luanics/cards/Error.hpp"
#include "luanics/cards/Rank.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <iostream>
#include <string>

namespace {

constexpr auto TWO_STRING = "TWO";
constexpr auto THREE_STRING = "THREE";
constexpr auto FOUR_STRING = "FOUR";
constexpr auto FIVE_STRING = "FIVE";
constexpr auto SIX_STRING = "SIX";
constexpr auto SEVEN_STRING = "SEVEN";
constexpr auto EIGHT_STRING = "EIGHT";
constexpr auto NINE_STRING = "NINE";
constexpr auto TEN_STRING = "TEN";
constexpr auto JACK_STRING = "JACK";
constexpr auto QUEEN_STRING = "QUEEN";
constexpr auto KING_STRING = "KING";
constexpr auto ACE_STRING = "ACE";

}

namespace luanics {
namespace cards {

//*****************************************************************************
// Queries
//*****************************************************************************

bool isLess(Rank const lhs, Rank const rhs, bool const isAceHigh) {
	CREATE ANSWER(
	return distance(lhs, rhs, isAceHigh) > 0;
	)
}

int distance(Rank const lhs, Rank const rhs, bool const isAceHigh) {
	CREATE ANSWER(
	int leftValue = static_cast<int>(lhs);
	if (lhs == Rank::ACE and not isAceHigh) {
		leftValue = 1;
	}
	int rightValue = static_cast<int>(rhs);
	if (rhs == Rank::ACE and not isAceHigh) {
		rightValue = 1;
	}
	return rightValue - leftValue;
	)
}

bool isFace(Rank const rank) {
	CREATE ANSWER(
	return rank == Rank::JACK or rank == Rank::QUEEN or rank == Rank::KING;
	)
}

//*****************************************************************************
// IO
//*****************************************************************************

std::ostream & operator<<(std::ostream & out, Rank const & rank) {
	switch (rank) {
		case Rank::TWO: out << TWO_STRING; break;
		case Rank::THREE: out << THREE_STRING; break;
		case Rank::FOUR: out << FOUR_STRING; break;
		case Rank::FIVE: out << FIVE_STRING; break;
		case Rank::SIX: out << SIX_STRING; break;
		case Rank::SEVEN: out << SEVEN_STRING; break;
		case Rank::EIGHT: out << EIGHT_STRING; break;
		case Rank::NINE: out << NINE_STRING; break;
		case Rank::TEN: out << TEN_STRING; break;
		case Rank::JACK: out << JACK_STRING; break;
		case Rank::QUEEN: out << QUEEN_STRING; break;
		case Rank::KING: out << KING_STRING; break;
		case Rank::ACE: out << ACE_STRING; break;
		default: throw Error{"Invalid Rank value:" + std::to_string(static_cast<uint8_t>(rank))};
	}
	return out;
}

std::istream & operator>>(std::istream & in, Rank & rank) {
	std::string s;
	in >> s;

	if (s == TWO_STRING) rank = Rank::TWO;
	else if (s == THREE_STRING) rank = Rank::THREE;
	else if (s == FOUR_STRING) rank = Rank::FOUR;
	else if (s == FIVE_STRING) rank = Rank::FIVE;
	else if (s == SIX_STRING) rank = Rank::SIX;
	else if (s == SEVEN_STRING) rank = Rank::SEVEN;
	else if (s == EIGHT_STRING) rank = Rank::EIGHT;
	else if (s == NINE_STRING) rank = Rank::NINE;
	else if (s == TEN_STRING) rank = Rank::TEN;
	else if (s == JACK_STRING) rank = Rank::JACK;
	else if (s == QUEEN_STRING) rank = Rank::QUEEN;
	else if (s == KING_STRING) rank = Rank::KING;
	else if (s == ACE_STRING) rank = Rank::ACE;
	else throw Error("Invalid rank string:" + s);

	return in;
}

}  // namespace cards
}  // namespace luanics
