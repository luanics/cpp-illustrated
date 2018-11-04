#pragma once

#include <iostream>

namespace luanics::utility {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Herald
///
/// @brief "Heralds" the beginning and ending of a block.
///
/// Generally used in the book code to bookend the start and end of main()
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Herald {
public:
	Herald(char const * const name, std::ostream * out = &std::cout) :
		_out{out}, _name{name}
	{
		*_out << "starting " << _name << " ..." << std::endl;
	}
	~Herald() {
		*_out << "... finished " << _name << std::endl;
	}

private:
	std::ostream * _out;
	char const * _name;
};

} // namespace luanics::utility
