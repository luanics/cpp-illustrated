#include <cassert>
#include <iostream>

#define BAD_MULTIPLY(a,b) a * b
#define GOOD_MULTIPLY(a,b) (a) * (b)

int main(int argc, char ** argv) {
	int const x = BAD_MULTIPLY(1+1,2);
	assert(x == 3);

	int const y = GOOD_MULTIPLY(1+1,2);
	assert(y == 4);

	return 0;
}
