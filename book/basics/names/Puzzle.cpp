#include <iostream>

int x;
namespace Y {
	int a;
  void f(float) {}
  void h(int) {}
}
namespace Z {
  void h(double) {}
}
namespace A {
  using namespace Y;
  void f(int) {}
  void g(int) {}
  void g() {}
  int i;
}
namespace B {
  using namespace Z;
  void f(char) {}
  int i;
}
namespace AB {
  using namespace A;
  using namespace B;
  void g() {A::i = 2;}
	void A() {g();}
}
void h()
{
	int AB; // OK - this won't interfere with names below as nested name specifiers don't match variables
  AB::g();  // AB is searched, AB::g found by lookup and is chosen AB::g(void)
            // (A and B are not searched)
  AB::f(1); // First, AB is searched, there is no f
            // Then, A, B are searched
            // A::f, B::f found by lookup (but Y is not searched so Y::f is not considered)
            // overload resolution picks A::f(int)
//  AB::x++;    // First, AB is searched, there is no x
              // Then A, B are searched. There is no x
              // Then Y and Z are searched. There is still no x: this is an error
//  AB::i++;  // AB is searched, there is no i
            // Then A, B are searched. A::i and B::i found by lookup: this is an error
  AB::h(16.8);  // First, AB is searched: there is no h
                // Then A, B are searched. There is no h
                // Then Y and Z are searched.
                // lookup finds Y::h and Z::h. Overload resolution picks Z::h(double)
}

int main(int argc, char ** argv) {

	return 0;
}
