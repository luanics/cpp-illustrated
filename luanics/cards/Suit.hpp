#pragma once

#include <cstdint>
#include <iosfwd>

namespace luanics::cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @enum Suit
///
/// @brief Suit in a standard deck of cards.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
enum class Suit {
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

static constexpr size_t NUM_SUITS = 4;

//////////////////////////////////////////////////////////////////
/// @name Queries
//////////////////////////////////////////////////////////////////
//@{
bool isBlack(Suit const & suit);
bool isRed(Suit const & suit);
//@}

//////////////////////////////////////////////////////////////////
/// @name IO
//////////////////////////////////////////////////////////////////
//@{
std::ostream & operator<<(std::ostream & out, Suit const & suit);
std::istream & operator>>(std::istream & in, Suit & suit);
//@}

} // namespace luanics::cards
