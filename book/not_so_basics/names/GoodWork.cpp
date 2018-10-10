#include "GoodWork.hpp"
#include <iostream>
#include <string>
namespace { // unnamed namespace
void print(std::string const & s) {
	std::cout << s << std::endl;
}
}
void goodWork() {
	print("work");
}
