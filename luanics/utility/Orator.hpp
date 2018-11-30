#pragma once

#include <iostream>

namespace luanics::utility {

class Orator {
public:
	Orator() {
		std::cout << "default constructor" << std::endl;
	}
	Orator(Orator const & other) {
		std::cout << "copy constructor" << std::endl;
	}
	Orator & operator=(Orator const & other) {
		std::cout << "copy assignment" << std::endl;
		return *this;
	}
	Orator(Orator && other) {
		std::cout << "move constructor" << std::endl;
	}
	Orator & operator=(Orator && other) {
		std::cout << "move assignment" << std::endl;
		return *this;
	}
	~Orator() {
		std::cout << "destructor" << std::endl;
	}
}; // class Orator

} // namespace luanics::utility
