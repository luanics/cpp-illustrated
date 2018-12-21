#pragma once

#include "luanics/cards/Model.hpp"

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class AbstractModel
///
/// @brief Skeleton implementation of Model.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class AbstractModel : public Model {
public:
	using Offset = luanics::graphics::Offset;

	AbstractModel(Offset const & textOffset);

	virtual bool isWon() const = 0;
	virtual bool isFinished() const;

	/// @returns true if valid move, false if not
	virtual bool move(unsigned const fromIndex, unsigned const toIndex) override final;
	/// After this call, piles() is populated.
	virtual void start() = 0;
	virtual void finish() override final;

	virtual void setText(std::string text) override final;

	virtual void paint(CardPainter const & cardPainter, FlippedGrid & grid) const override final;

private:
	struct PileInfo {
		Pile * pile;
		Offset offset;
	};

	virtual std::vector<PileInfo> & pileInfos() = 0;
	virtual std::vector<PileInfo> const & pileInfos() const = 0;

	Offset _textOffset;
	bool _isFinishRequested;
	std::string _text;
}; // class AbstractModel

} // namespace cards
} // namespace luanics
