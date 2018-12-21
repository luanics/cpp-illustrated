#include "../pile/Cell.hpp"

#include "luanics/logging/Contract.hpp"

namespace luanics {
namespace cards {

Cell::Cell() : _cards{} {

}

bool Cell::isEmpty() const {
	return _cards.empty();
}

void Cell::clear() {
	_cards.clear();
}

Cell::CardsType const & Cell::cards() const {
	return _cards;
}

bool Cell::put(Card const & card) {
	if (not isEmpty()) {
		return false;
	}
	_cards.push_back(card);
	return true;
}

bool Cell::take(Card & card) {
	if (isEmpty()) {
		return false;
	}
	card = _cards.back();
	_cards.pop_back();
	return true;
}

void Cell::untake(Card const & returned) {
	PRECONDITION(isEmpty());
	_cards.push_back(returned);
}

void Cell::paint(
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

}  // namespace cards
}  // namespace luanics
