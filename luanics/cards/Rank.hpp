#pragma once

#include <cstdint>
#include <iosfwd>

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @enum Rank
///
/// @brief Rank in a standard deck of cards.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
enum class Rank {
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

static constexpr size_t NUM_RANKS = 13;

//////////////////////////////////////////////////////////////////
/// @name Queries
//////////////////////////////////////////////////////////////////
//@{
/// @returns true if lhs < rhs
bool isLess(Rank const lhs, Rank const rhs, bool const isAceHigh);
/// @returns num promotions needed to go from lhs to rhs
int distance(Rank const lhs, Rank const rhs, bool const isAceHigh);
/// @returns true for JACK, QUEEN, and KING
bool isFace(Rank const rank);
//@}

//////////////////////////////////////////////////////////////////
/// @name IO
//////////////////////////////////////////////////////////////////
//@{
std::ostream & operator<<(std::ostream & out, Rank const & rank);
std::istream & operator>>(std::istream & in, Rank & rank);
//@}

}  // namespace cards
}  // namespace luanics
