#include "luanics/utility/Herald.hpp"

//*********************************************************
// Naming
//*********************************************************

class Class {
	int _member;
};

int * pNumber;

auto pszMessage = "Hello"; // (p)ointer to (z)ero-terminated (s)tring

class Program {
public:
	std::string const & title() const; // query -> noun
	void run();                        // action -> verb
};

namespace bad {
enum Personality { // Bad
	SHY,
	EXTROVERT
};
}

namespace good {
enum Personality { // Good
	INTROVERT,
	EXTROVERT
};
}





//*********************************************************
// Commenting
//*********************************************************

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Doodad
///
/// @brief A dad that gets it done.
///
/// @tparam ActionT The doings of the Doodad.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <typename ActionT>
class Doodad {

};

int main() {
	luanics::utility::Herald herald{"Conventions"};

	return 0;
}
