#include "Hand.hpp"

#include <luanics/utility/Strings.hpp>

namespace luanics::cards::blackjack {

Hand::Hand() :
	_cards{}, _score{0}
{}

void Hand::add(Card const & card) {
	_cards.push_back(card);
	updateScore();
}

void Hand::clear() {
	_cards.clear();
	_score = 0;
}

std::vector<Card> const & Hand::cards() const {
	return _cards;
}

bool Hand::isBust() const {
	return _score == bustScore;
}

int Hand::score() const {
	return _score;
}

void Hand::updateScore() {
	int numAces = 0;
	_score = 0;
	// Determine score without aces
	for (auto const & card: _cards) {
		if (card.rank() == Rank::ACE) {
			++numAces;
		}
		else if (isFace(card.rank())) {
			_score += 10;
		}
		else {
			_score += 1 + distance(Rank::ACE, card.rank(), false);
		}
	}
	// Add in aces. They can be worth 1 or 11
	_score += numAces; // ... each ace worth at least one
	int gap = bestScore - _score;
	int const gapInTens = gap / 10;
	int const numAcesActivated = std::max(0, std::min(gapInTens, numAces));
	_score += numAcesActivated * 10;

	// Check if bust
	if (_score > bestScore) {
		_score = bustScore;
	}
}

std::ostream & operator<<(std::ostream & out, Hand const & hand) {
	if (hand.isBust()) {
		out << "BUST";
	}
	else {
		out << hand.score();
	}
	out << " (";
	utility::strings::join(hand.cards(), out, ",");
	out << ")";
	return out;
}

} // namespace luanics::cards::blackjack
