#include <cassert>
#include <iostream>

//*********************************************************
// Macros
//*********************************************************

#define PI 3.14157
double const radius = 1.0;
double const circumference = 2.0 * PI * radius;

#define MAX(a,b) ((a) > (b) ? (a) : (b))

//*********************************************************
// Macro Pitfalls
//*********************************************************

#define BAD_MULTIPLY(a,b) a * b
#define GOOD_MULTIPLY(a,b) ((a) * (b))

//*********************************************************
// Preprocessor Operators
//*********************************************************

#define PRINT(x) std::cout << #x << "=" << (x) << std::endl
#define DEFINE_VALUE(type) type type##Value

int main(int argc, char ** argv) {

	//*********************************************************
	// Macros
	//*********************************************************
   std::cout << MAX(1,2) << std::endl;

   //*********************************************************
	// Macro Pitfalls
	//*********************************************************
   int x = BAD_MULTIPLY(1+1,2);
   std::cout << "x = " << x << std::endl;
   int y = GOOD_MULTIPLY(1+1,2);
   std::cout << "y = " << y << std::endl;

   //*********************************************************
	// Preprocessor Operators
	//*********************************************************
   int z = 10;
   PRINT(z);
   DEFINE_VALUE(int);
   DEFINE_VALUE(float);
   std::cout << "You are at " << __FILE__ << "[" << __LINE__ << "]" << std::endl;

	return 0;
}
