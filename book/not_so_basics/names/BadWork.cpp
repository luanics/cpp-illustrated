#include "BadWork.hpp"
#include <iostream>
#include <string>
// global namespace
void print(std::string const & s) {
	std::cout << s << std::endl;
}
void badWork() {
	print("work");
}
