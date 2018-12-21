#pragma once

namespace luanics {
	class FlippedGrid;
	namespace graphics { class Point; }
namespace cards {
	class Card;
	class CardPainter;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Pile
///
/// @brief A stack of cards with particular rules about putting and taking.
///
/// @see https://en.wikipedia.org/wiki/Glossary_of_patience_terms
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Pile {
public:
	using Point = luanics::graphics::Point;

	/// @returns true if valid move
	/// @param[in] placed holds card being put
	virtual bool put(Card const & placed) = 0;
	/// @returns true if valid move
	/// @param[out] removed holds card taken if valid move
	virtual bool take(Card & removed) = 0;
	/// @param[in] returned holds card that was removed
	virtual void untake(Card const & returned) = 0;

	virtual void paint(
		CardPainter const & cardPainter,
		Point const & topLeft,
		FlippedGrid & grid
	);

	virtual ~Pile() {}
}; // class Stack

}  // namespace cards
}  // namespace luanics
