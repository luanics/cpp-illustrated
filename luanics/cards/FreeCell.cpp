#include "luanics/cards/FreeCell.hpp"

namespace luanics {
namespace cards {
namespace {

graphics::Offset const HORIZONTAL_SPACE{1, 0};
graphics::Offset const VERTICAL_SPACE{0,4};
graphics::Point const STARTING_POINT{2,2};
graphics::Offset const FOUNDATIONS_START = STARTING_POINT + graphics::Offset{2,2};
graphics::Offset const CELLS_START =

constexpr bool IS_ACE_HIGH= false;
constexpr unsigned NUM_CASCADES= 8;
constexpr unsigned NUM_CELLS = 4;
constexpr unsigned NUM_FOUNDATIONS= 4;
constexpr unsigned NUM_PILES = NUM_CASCADES + NUM_CELLS + NUM_FOUNDATIONS;

}

FreeCell::FreeCell() :
	AbstractModel{Offset{1,1}},
	_cascades{NUM_CASCADES, {IS_ACE_HIGH}},
	_cells{NUM_CELLS},
	_foundations{NUM_FOUNDATIONS, {IS_ACE_HIGH}},
	_pileInfos{}
{

}

bool FreeCell::isWon() const {
	return std::all_of(
		_foundations.begin(),
		_foundations.end(),
		[](Foundation const & foundation){return foundation.isComplete();}
	);
}

void FreeCell::start() {
	// Clear all piles
	for (Cascade & cascade: _cascades) {
		cascade.clear();
	}
	for (Cell & cell: _cells) {
		cell.clear();
	}
	for (Foundation & foundation: _foundations) {
		foundation.clear();
	}

	// Populate cascades
	Deck deck;
	deck.shuffle();
	unsigned cascadeIndex = 0;
	while (not deck.isEmpty()) {
		_cascades[cascadeIndex].add(deck.draw());
		cascadeIndex = (cascadeIndex + 1) % Model::NUM_CASCADES;
	}
}

std::vector<AbstractModel::PileInfo> & FreeCell::pileInfos() {
	return _pileInfos;
}

std::vector<AbstractModel::PileInfo> const & FreeCell::pileInfos() const {
	return _pileInfos;
}

} // namespace cards
} // namespace luanics
