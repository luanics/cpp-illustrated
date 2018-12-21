#include "luanics/utility/Hash.hpp"
#include "luanics/cards/Deck.hpp"
#include "luanics/cards/freecell/Model.hpp"
#include "luanics/cards/freecell/StackId.hpp"

#include <algorithm>
#include <iterator>
#include <unordered_map>

namespace {

using luanics::cards::freecell::StackId;
using luanics::cards::freecell::Model;

unsigned indexFor(StackId const & id) {
	switch (id.category()) {
		case StackId::CASCADE: return Model::NUM_FOUNDATIONS + Model::NUM_CELLS + id.index();
		case StackId::CELL: return Model::NUM_FOUNDATIONS + id.index();
		case StackId::FOUNDATION: return id.index();
	}
}

//std::vector<luanics::cards::Card> cascadeCards() {
//	using namespace luanics::cards;
//	std::vector<Card> result;
//	result.reserve(NUM_RANKS * NUM_SUITS);
//	for (size_t suitIndex = 0; suitIndex < NUM_SUITS; ++suitIndex) {
//		Suit const suit = static_cast<Suit>(suitIndex);
//		for (size_t rankIndex = 2; rankIndex < NUM_RANKS + 2; ++rankIndex) {
//			Rank const rank = static_cast<Rank>(rankIndex);
//			result.push_back(Card(rank, suit));
//		}
//	}
//	return result;
//}

}

namespace luanics {
namespace cards {
namespace freecell {

Model::Model() :
	_foundations{},
	_cells{},
	_cascades{},
	_stacks{},
	_text{},
	_isFinished{false}
{
	registerStacks();
}

Model::FoundationsType const & Model::foundations() const {
	return _foundations;
}

Model::CellsType const & Model::cells() const {
	return _cells;
}

Model::CascadesType const & Model::cascades() const {
	return _cascades;
}

std::string const & Model::text() const {
	return _text;
}

void Model::setText(std::string text) {
	_text = std::move(text);
}

bool Model::isWon() const {
	return std::all_of(
		_foundations.begin(),
		_foundations.end(),
		[](Foundation const & foundation){return foundation.isComplete();}
	);
}

bool Model::isFinished() const {
	return _isFinished or isWon();
}

bool Model::move(StackId const & from, StackId const & to) {
	Card moved;
	auto const fromStackIndex = indexFor(from);
	Pile * fromStack = _stacks[fromStackIndex];
	if (not fromStack->take(moved)) {
		return false;
	}
	auto const toStackIndex = indexFor(to);
	Pile * toStack = _stacks[toStackIndex];
	if (not toStack->put(moved)) {
		fromStack->untake(moved);
		return false;
	}

	return true;
}

void Model::start() {
//	_foundations[0].put(Card{Rank::ACE, Suit::CLUBS});
//	_foundations[1].put(Card{Rank::ACE, Suit::DIAMONDS});
//	_foundations[2].put(Card{Rank::ACE, Suit::HEARTS});
//	_foundations[3].put(Card{Rank::ACE, Suit::SPADES});

	Deck deck;
	deck.shuffle();
	unsigned cascadeIndex = 0;
	while (not deck.isEmpty()) {
		_cascades[cascadeIndex].add(deck.draw());
		cascadeIndex = (cascadeIndex + 1) % Model::NUM_CASCADES;
	}
}

void Model::finish() {
	_isFinished = true;
}

void Model::registerStacks() {
	unsigned stackIndex = 0;
	for (auto & foundation: _foundations) {
		_stacks[stackIndex++] = &foundation;
	}
	for (auto & cell: _cells) {
		_stacks[stackIndex++] = &cell;
	}
	for (auto & cascade: _cascades) {
		_stacks[stackIndex++] = &cascade;
	}
}

}  // namespace freecell
}  // namespace cards
}  // namespace luanics
