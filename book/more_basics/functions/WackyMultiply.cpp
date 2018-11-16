#include "BadAdd.hpp"
#include "WackyMultiply.hpp"

int wackyMultiply(int const x, int const y) {
	int result{};
	for (int i = 0; i < x; ++i) {
		result = badAdd(result, y);
	}
	return result;
}
