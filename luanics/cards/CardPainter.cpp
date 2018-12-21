#include "luanics/cards/Card.hpp"
#include "luanics/cards/CardPainter.hpp"
#include "luanics/container/FlippedGrid.hpp"
#include "luanics/graphics/Painter.hpp"
#include "luanics/graphics/Point.hpp"
#include "luanics/graphics/Rectangle.hpp"

namespace {

using Brush = luanics::graphics::Brush;
using Offset = luanics::graphics::Offset;
using Rectangle = luanics::graphics::Rectangle;
using Rank = luanics::cards::Rank;
using Suit = luanics::cards::Suit;

Brush const defaultFaceUpBrush{'*', ' '};
Brush const defaultFaceDownBrush{'*', '#'};
Offset const defaultCardSize{6,5};
Offset const defaultNameOffset{1,1};
Offset const defaultColorOffset{5,1};

char charFor(Rank const rank) {
	switch (rank) {
		case Rank::TWO: return '2';
		case Rank::THREE: return '3';
		case Rank::FOUR: return '4';
		case Rank::FIVE: return '5';
		case Rank::SIX: return '6';
		case Rank::SEVEN: return '7';
		case Rank::EIGHT: return '8';
		case Rank::NINE: return '9';
		case Rank::TEN: return 'T';
		case Rank::JACK: return 'J';
		case Rank::QUEEN: return 'Q';
		case Rank::KING: return 'K';
		case Rank::ACE: return 'A';
		default: return ' ';
	}
}

char charFor(Suit const suit) {
	switch (suit) {
		case Suit::CLUBS: return 'C';
		case Suit::DIAMONDS: return 'D';
		case Suit::HEARTS: return 'H';
		case Suit::SPADES: return 'S';
		default: return ' ';
	}
}

}
namespace luanics {
namespace cards {

CardPainter::CardPainter() :
	CardPainter{
		defaultFaceUpBrush,
		defaultFaceDownBrush,
		defaultCardSize,
		defaultNameOffset,
		defaultColorOffset
	}
{}

CardPainter::CardPainter(
	Brush const & faceUpBrush,
	Brush const & faceDownBrush,
	Offset const & cardSize,
	Offset const & nameOffset,
	Offset const & colorOffset
) :
	_faceUpBrush{faceUpBrush},
	_faceDownBrush{faceDownBrush},
	_cardSize{cardSize},
	_nameOffset{nameOffset},
	_colorOffset{colorOffset}
{}

CardPainter::Offset const & CardPainter::cardSize() const {
	return _cardSize;
}

void CardPainter::paintFaceUp(
	Point const & topLeft,
	Card const & card,
	FlippedGrid & grid
) const {
	Painter painter{&grid, _faceUpBrush};

	painter.paint(Rectangle{topLeft, topLeft + _cardSize});

	std::string const name = {charFor(card.rank()), charFor(card.suit())};
	painter.paint(name, topLeft + _nameOffset);

	std::string const color = isBlack(card.suit()) ? "B" : "r";
	painter.paint(color, topLeft +  _colorOffset);
}

void CardPainter::paintFaceDown(
	Point const & topLeft,
	Card const & card,
	FlippedGrid & grid
) const {
	Painter painter{&grid};

	painter.setBrush(_faceDownBrush);
	painter.paint(luanics::graphics::Rectangle{topLeft, topLeft + _cardSize});
}

void CardPainter::paintSpace(
	Point const & topLeft,
	FlippedGrid & grid
) const {
	Painter painter{&grid};

	painter.setBrush(Brush::empty());
	painter.paint(luanics::graphics::Rectangle{topLeft, topLeft + _cardSize});
}

} // namespace cards
} // namespace luanics
