#pragma once

#include <iostream>

namespace luanics {

class Herald {
public:
	Herald(char const * const name) : _name{name} {
		std::cout << "running " << _name << " ..." << std::endl;
	}
	~Herald() {
		std::cout << "... finished " << _name << std::endl;
	}
private:
	char const * _name;
};

} // namespace luanics
