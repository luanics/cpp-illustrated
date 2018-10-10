#include <cassert>

// This x lives at global scope
double x = 1.0;
int main(int argc, char ** argv) {
	// Until we're told otherwise,
	//  "x" refers to the one at global scope.
	assert(x == 1.0);

	// This x lives in "main" function body scope
	//  and hides the x at global scope at this point.
	int x = 2;
	assert(x == 2);
	{
		// This x lives in an unnamed scope in "main" function body
		//  and hides the x at "main" function body scope.
		char x = 'a';
		assert(x == 'a');
	}
	// Back in "main" function body scope...
	assert(x == 2);
}
