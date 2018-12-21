#pragma once

#include "luanics/cards/Controller.hpp"
#include "luanics/cards/Model.hpp"
#include "luanics/cards/CardPainter.hpp"
#include "luanics/container/DynamicGrid.hpp"

namespace luanics {
namespace cards {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Game
///
/// @brief Coordinates the various game components and run main loop.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Game {
public:
	Game(
		std::unique_ptr<Model> model,
		std::istream * in = &std::cin,
		std::ostream * out = &std::cout,
		unsigned const width = 90U,
		unsigned const height = 40U
	);

	void run();

private:
	void startUp();
	void shutDown();
	void runOnce();
	bool isFinished() const;
	void input();
	void update();
	void render();

	std::unique_ptr<Model> _model;
	Controller _controller;
	DynamicGrid _screen;
	CardPainter _cardPainter;
	Controller::ActionType _nextAction;
	std::ostream * _out;
}; // class Game

}  // namespace cards
}  // namespace luanics
