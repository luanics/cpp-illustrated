#include <iostream>

namespace A {

void f() {std::cout << "A0::f()" << std::endl;}

}

namespace B0 {
void f() {std::cout << "B0::f()" << std::endl;}
namespace B1 {
using namespace A;
void g() {
	using A::f;
//	using namespace A; // Strangely, f() still binds to B0::f() when uncommented...
	f();
}
}
}

int main(int argc, char ** argv) {

	B0::B1::g(); // prints "B0::f()" - how can we explain this?
	// Here is explanation: http://stackoverflow.com/questions/23582526/how-name-lookup-is-applied-in-namespaces

	return 0;
}
