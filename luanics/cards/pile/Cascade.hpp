#pragma once

#include "luanics/cards/Card.hpp"
#include "luanics/cards/Pile.hpp"

#include <vector>

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Cascade
///
/// @brief Initially an unordered pile of fanned cards, can develop a tableau on top.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Cascade : public Pile {
public:
	using CardsType = std::vector<Card>;

	/// Empty
	Cascade(bool const isAceHigh);
	/// With initial unordered cards
	Cascade(CardsType const & initial, bool const isAceHigh);
	/// @TODO check on generator based range construction
//	/// With numDraws cards drawn from deck
//	Cascade(Deck & deck, unsigned const numDraws);

	bool isEmpty() const;
	CardsType const & cards() const;

	void add(Card const & card);
	void clear();

	virtual bool put(Card const & placed) override final;
	virtual bool take(Card & removed) override final;
	virtual void untake(Card const & returned) override final;
	virtual void paint(
		CardPainter const & cardPainter,
		Point const & topLeft,
		FlippedGrid & grid
	) override final;

private:
	bool _isAceHigh;
	CardsType _cards;
}; // class Cascade

}  // namespace cards
}  // namespace luanics
