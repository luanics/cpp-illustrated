#include "luanics/utility/Hash.hpp"
#include "luanics/cards/Deck.hpp"
#include "luanics/cards/freecell/Game.hpp"
#include "luanics/cards/freecell/StackId.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_map>

namespace {
char constexpr EMPTY_CHAR = ' ';
}

namespace luanics {
namespace cards {

Game::Game(
	std::unique_ptr<Model> model,
	std::istream * in,
	std::ostream * out,
	unsigned const width,
	unsigned const height
) :
	_model{std::move(model)},
	_controller{in, _model},
	_screen{width, height},
	_cardPainter{},
	_out{out}
{}

void Game::run() {
	startUp();
	while (not isFinished()) {
		runOnce();
	}
	shutDown();
}

void Game::startUp() {
	_model->start();
	render();
}

void Game::shutDown() {

}

void Game::runOnce() {
	while (not isFinished()) {
		input();
		update();
		render();
	}
}

bool Game::isFinished() const {
	return _model->isFinished();
}

void Game::input() {
	_nextAction = _controller.nextAction();
}

void Game::update() {
	if (_nextAction) {
		_nextAction(_model);
		_model->setText(_model->isWon() ? "You won!" : "");
	}
	else {
		_model->setText("Invalid action");
	}
}

void Game::render() {
	// Flush once to get rid of orphans
	_screen.fillWith(EMPTY_CHAR);
	_screen.writeTo(*_out);

	_cardPainter.paintBoard();
	_cardPainter.paint(_model);
	_screen.writeTo(*_out);
}

}  // namespace cards
}  // namespace luanics
