#pragma once

#include "luanics/cards/pile/Cascade.hpp"
#include "luanics/cards/pile/Cell.hpp"
#include "luanics/cards/pile/Foundation.hpp"

#include <array>

namespace luanics {
namespace cards {

class StackId;

class Model {
public:
	static constexpr unsigned NUM_FOUNDATIONS = 4;
	static constexpr unsigned NUM_CELLS = 4;
	static constexpr unsigned NUM_CASCADES = 8;
	static constexpr unsigned NUM_STACKS = NUM_FOUNDATIONS + NUM_CELLS + NUM_CASCADES;
	using FoundationsType = std::array<Foundation, NUM_FOUNDATIONS>;
	using CellsType = std::array<Cell, NUM_CELLS>;
	using CascadesType = std::array<Cascade, NUM_CASCADES>;

	Model();

	FoundationsType const & foundations() const;
	CellsType const & cells() const;
	CascadesType const & cascades() const;

	std::string const & text() const;
	void setText(std::string text);

	void start();
	void finish();
	bool move(StackId const & from, StackId const & to);
	bool isWon() const;
	bool isFinished() const;

private:
	void registerStacks();

	FoundationsType _foundations;
	CellsType _cells;
	CascadesType _cascades;
	std::array<Pile *, NUM_STACKS> _stacks;
	std::string _text;
	bool _isFinished;
}; // class Model

}  // namespace cards
}  // namespace luanics
