#include "luanics/cards/Error.hpp"
#include "luanics/cards/Rank.hpp"
#include "luanics/testing/Tutorial.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

namespace luanics::cards {

namespace {

std::array<std::pair<Rank, std::string>, NUM_RANKS> rankStringPairs{{
	{Rank::TWO, "TWO"},
	{Rank::THREE, "THREE"},
	{Rank::FOUR, "FOUR"},
	{Rank::FIVE, "FIVE"},
	{Rank::SIX, "SIX"},
	{Rank::SEVEN, "SEVEN"},
	{Rank::EIGHT, "EIGHT"},
	{Rank::NINE, "NINE"},
	{Rank::TEN, "TEN"},
	{Rank::JACK, "JACK"},
	{Rank::QUEEN, "QUEEN"},
	{Rank::KING, "KING"},
	{Rank::ACE, "ACE"}
}};

}

//*****************************************************************************
// Queries
//*****************************************************************************

bool isLess(Rank const lhs, Rank const rhs, bool const isAceHigh) {
//	CREATE ANSWER(
	return distance(lhs, rhs, isAceHigh) > 0;
//	)
}

int distance(Rank const lhs, Rank const rhs, bool const isAceHigh) {
//	CREATE ANSWER(
	int leftValue = static_cast<int>(lhs);
	if (lhs == Rank::ACE and not isAceHigh) {
		leftValue = 1;
	}
	int rightValue = static_cast<int>(rhs);
	if (rhs == Rank::ACE and not isAceHigh) {
		rightValue = 1;
	}
	return rightValue - leftValue;
//	)
}

bool isFace(Rank const rank) {
//	CREATE ANSWER(
	return rank == Rank::JACK or rank == Rank::QUEEN or rank == Rank::KING;
//	)
}

//*****************************************************************************
// IO
//*****************************************************************************

std::ostream & operator<<(std::ostream & out, Rank const & rank) {
	int const index = distance(Rank::TWO, rank, true);
	bool const isInvalid = index < 0;
	if (isInvalid) {
		throw Error{"Invalid Rank value:" + std::to_string(static_cast<uint8_t>(rank))};
	}
	out << rankStringPairs[index].second;
	return out;
}

std::istream & operator>>(std::istream & in, Rank & rank) {
	std::string s;
	in >> s;

	auto const position = std::find_if(
		rankStringPairs.begin(),
		rankStringPairs.end(),
		[&s](auto const & pair){return pair.second == s;}
	);
	bool const isFound = position != rankStringPairs.end();
	if (not isFound) {
		throw Error("Invalid rank string:" + s);
	}
	rank = position->first;
	return in;
}

} // namespace luanics::cards
