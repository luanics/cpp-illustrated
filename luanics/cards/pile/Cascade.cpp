#include "luanics/cards/Deck.hpp"
#include "luanics/cards/pile/Cascade.hpp"


namespace luanics {
namespace cards {

Cascade::Cascade(bool const isAceHigh) :
	_isAceHigh{isAceHigh},
	_cards{}
{}

Cascade::Cascade(CardsType const & cards, bool const isAceHigh) :
	_isAceHigh{isAceHigh},
	_cards{cards}
{}

void Cascade::add(Card const & card) {
	_cards.push_back(card);
}

void Cascade::clear() {
	_cards.clear();
}

bool Cascade::isEmpty() const {
	return _cards.empty();
}

Cascade::CardsType const & Cascade::cards() const {
	return _cards;
}

bool Cascade::put(Card const & placed) {
	if (not isEmpty()) {
		Card const & topCard = _cards.back();
		bool const isCorrectRank = distance(placed.rank(), topCard.rank(), _isAceHigh) == 1;
		bool const isCorrectSuit = isBlack(placed.suit()) xor isBlack(topCard.suit());
		if (not isCorrectRank or not isCorrectSuit) {
			return false;
		}
	}
	_cards.push_back(placed);
	return true;
}

bool Cascade::take(Card & removed) {
	if (isEmpty()) {
		return false;
	}
	removed = _cards.back();
	_cards.pop_back();
	return true;
}

void Cascade::untake(Card const & returned) {
	_cards.push_back(returned);
}

void Cascade::paint(
	CardPainter const & cardPainter,
	Point const & topLeft,
	FlippedGrid & grid
) {
	if (isEmpty()) {
		cardPainter.paintSpace(topLeft, grid);
	}
	else {
		auto current = topLeft;
		luanics::graphics::Offset const fanOffset{0, 2};
		for (auto const & card: cards()) {
			cardPainter.paintFaceUp(current, card, grid);
			current += fanOffset;
		}
	}
}

}  // namespace cards
}  // namespace luanics
