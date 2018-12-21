#include "luanics/cards/Controller.hpp"
#include "luanics/cards/Model.hpp"


namespace luanics {
namespace cards {

namespace {

constexpr char QUIT_CHAR = 'q';
constexpr char HELP_CHAR = '?';

}

Controller::Controller(std::istream * in, Model const & model) :
	_in{in}
{}

Controller::ActionType Controller::nextAction() {
	char choice;
	*_in >> choice;
	if (choice == QUIT_CHAR) {
		return [](Model & m){m.finish();};
	}
	else if (choice == HELP_CHAR) {
		return [](Model & m){m.help();};
	}

	bool const isMoreInput = static_cast<bool>(*_in);
	if (not isMoreInput) {
		return ActionType{};
	}
	unsigned const fromIndex = static_cast<unsigned>(choice);

	*_in >> choice;
	unsigned const toIndex = static_cast<unsigned>(choice);

	return [=](Model & m){m.move(fromIndex, toIndex);};
}

}  // namespace cards
}  // namespace luanics
