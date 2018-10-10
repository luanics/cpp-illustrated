#include "Car.hpp"

// Implementation

int Car::speedInMph() const {return speedInMph_;}

void Car::go() {speedInMph_ = 60;}

void Car::stop() {speedInMph_ = 0;}
