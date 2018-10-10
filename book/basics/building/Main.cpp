#include "Car.hpp"
#include <iostream>

int main() {
	Car speedy;
	std::cout << "Go, Speedy!" << std::endl;
	speedy.go();
	std::cout << "Speedy's speed is " << speedy.speedInMph() << std::endl;
	return 0; // Success!
}
