#pragma once

#include "luanics/cards/AbstractModel.hpp"

namespace luanics {
namespace cards {

class FreeCell : public AbstractModel {
public:
	using FoundationsType = std::vector<Foundation>;
	using CellsType = std::vector<Cell>;
	using CascadesType = std::vector<Cascade>;

	FreeCell();

	virtual bool isWon() const override final;
	virtual void start() override final;

private:
	virtual std::vector<PileInfo> & pileInfos() override final;
	virtual std::vector<PileInfo> const & pileInfos() const override final;

	CascadesType _cascades;
	CellsType _cells;
	FoundationsType _foundations;
	std::vector<PileInfo> _pileInfos;
}; // class FreeCell

} // namespace cards
} // namespace luanics
