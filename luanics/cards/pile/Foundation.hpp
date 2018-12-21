#pragma once

#include "luanics/cards/Card.hpp"
#include "luanics/cards/Pile.hpp"

#include <vector>

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Foundation
///
/// @brief A squared "destination" pile, formed of consecutive ascending cards of single suit.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Foundation :  public Pile {
public:
	using CardsType = std::vector<Card>;

	/// Empty foundation
	Foundation(bool const isAceHigh);

	bool isEmpty() const;
	bool isComplete() const;
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
	bool _isAceHigh;
	CardsType _cards;
}; // class Foundation

}  // namespace cards
}  // namespace luanics
