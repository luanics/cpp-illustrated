#pragma once

#include <luanics/cards/Card.hpp>

#include <iostream>
#include <vector>

namespace luanics::cards::blackjack {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class blackjack::Hand
///
/// @brief A hand of cards.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Hand {
public:
	static constexpr int bestScore = 21;
	static constexpr int bustScore = -1;

	Hand(); ///< Empty hand

	void add(Card const & card);
	void clear();
	std::vector<Card> const & cards() const;

	bool isBust() const; ///< true if when score() passes 21
	int score() const; ///< -1 if isBust()

private:
	void updateScore();

	std::vector<Card> _cards;
	int _score;
}; // class Hand

/// Output is <score> (<cards>)
std::ostream & operator<<(std::ostream & out, Hand const & hand);

} // namespace luanics::cards::blackjack
