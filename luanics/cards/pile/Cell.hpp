#pragma once

#include "luanics/cards/Pile.hpp"
#include "luanics/cards/Card.hpp"

#include <vector>

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Cell
///
/// @brief The "Cell" in "FreeCell". Storage for up to one card.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Cell : public Pile {
public:
	using CardsType = std::vector<Card>;

	/// Empty cell
	Cell();

	bool isEmpty() const;
	CardsType const & cards() const;
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
	CardsType _cards;
}; // class Cell

}  // namespace cards
}  // namespace luanics
