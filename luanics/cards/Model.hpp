#pragma once

#include <string>

namespace luanics {
	class FlippedGrid;
namespace cards {
	class CardPainter;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Model
///
/// @brief Stores the game state and layout.
///
/// The game "Model" in the sense of Model/View.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Model {
public:
	virtual bool isWon() const = 0;
	virtual bool isFinished() const = 0;

	virtual void move(unsigned const fromIndex, unsigned const toIndex) = 0;
	/// Request to (re)start the game with a clean slate.
	virtual void start() = 0;
	/// Request to end the game.
	virtual void finish() = 0;

	virtual void setText(std::string text) = 0;
	virtual void paint(CardPainter const & cardPainter, FlippedGrid & grid) const = 0;

	virtual ~Model() = default;
}; // class Model

} // namespace cards
} // namespace luanics
