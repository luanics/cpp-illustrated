#include "luanics/cards/AbstractModel.hpp"
#include "luanics/cards/PaintHelpers.hpp"

namespace luanics {
namespace cards {

AbstractModel::AbstractModel(Offset const & textOffset) :
	_textOffset{textOffset},
	_text{},
	_isFinishRequested{false}
{}

bool AbstractModel::isFinished() const {
	return isWon() or _isFinishRequested;
}

bool AbstractModel::move(unsigned const fromIndex, unsigned const toIndex) {
	Card moved;
	auto const numPiles = pileInfos().size();
	bool const areIndicesValid =
		fromIndex < numPiles
		and toIndex < numPiles
		and fromIndex != toIndex;
	if (not areIndicesValid) {
		return false;
	}
	Pile * fromPile = pileInfos()[fromIndex].pile;
	Pile * toPile = pileInfos()[toIndex].pile;
	if (not fromPile->take(moved)) {
		return false;
	}
	if (not toPile->put(moved)) {
		fromPile->untake(moved);
		return false;
	}
	return true;
}

void AbstractModel::finish() {
	_isFinishRequested = true;
}

void AbstractModel::setText(std::string text) {
	_text = std::move(text);
}

void AbstractModel::paint(CardPainter const & cardPainter, FlippedGrid & grid) const {
	for (auto const & pileInfo: pileInfos()) {
		Offset const & topLeft = pileInfo.offset;
		paintFrame(cardPainter.cardSize(), topLeft - Offset{1,1}, grid);
		pileInfo.pile->paint(cardPainter, pileInfo.offset, grid);
	}
}

} // namespace cards
} // namespace luanics
