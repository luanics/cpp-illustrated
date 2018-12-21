#include "luanics/cards/pile/Foundation.hpp"

namespace luanics {
namespace cards {

Foundation::Foundation(bool const isAceHigh) :
	_isAceHigh{isAceHigh},
	_cards{}
{}

bool Foundation::isEmpty() const {
	return _cards.empty();
}

bool Foundation::isComplete() const {
	return _cards.size() == NUM_RANKS;
}

Foundation::CardsType const & Foundation::cards() const {
	return _cards;
}

void Foundation::clear() {
	_cards.clear();
}

bool Foundation::put(Card const & placed) {
	if (isEmpty()) {
		bool const isCorrectRank = placed.rank() == Rank::ACE;
		if (not isCorrectRank) {
			return false;
		}
	}
	else {
		Card const & topCard = _cards.back();
		bool const isCorrectRank = distance(topCard.rank(), placed.rank(), _isAceHigh) == 1;
		bool const isCorrectSuit = topCard.suit() == placed.suit();
		if (not isCorrectRank or not isCorrectSuit) {
			return false;
		}
	}
	_cards.push_back(placed);
	return true;
}

bool Foundation::take(Card & removed) {
	if (isEmpty()) {
		return false;
	}
	removed = _cards.back();
	_cards.pop_back();
	return true;
}

void Foundation::paint(
	CardPainter const & cardPainter,
	Point const & topLeft,
	FlippedGrid & grid
) {
	if (isEmpty()) {
		cardPainter.paintSpace(topLeft, grid);
	}
	else {
		cardPainter.paintFaceUp(topLeft, cards().back(), grid);
	}
}

void Foundation::untake(Card const & returned) {
	bool const isReturned = put(returned);
	ASSERT(isReturned);
}

}  // namespace cards
}  // namespace luanics
