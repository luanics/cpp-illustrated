#include "luanics/utility/Herald.hpp"

#include <cassert>

//*********************************************************
// Implicit conversions
//*********************************************************

double square(double x) {return x*x;}

//*********************************************************
// User-defined conversions
//*********************************************************

class Int {
public:
	Int(int value) : _value{value} {} // Constructor
	void add(Int const & other) {_value += other._value;}
	operator int() {return _value;}   // Conversion function
private:
	int _value;
};

class ExplicitInt {
public:
	explicit ExplicitInt(int value) : _value{value} {}
	void add(ExplicitInt const & other) {_value += other._value;}
	explicit operator int() {return _value;}
private:
	int _value;
};

//*********************************************************
// Explicit conversions
//*********************************************************
struct Base {
	virtual int value() const = 0;
	virtual ~Base() = default;
};
struct Derived1 : Base {
	virtual int value() const override final {return value_;}
	int value_;
};
struct Derived2 : Base {
	virtual int value() const override final {return 1;}
};

int main() {
	//*********************************************************
	// Implicit Conversions
	//*********************************************************

	int const four = square(2);
	std::cout << "square(2) ~ " << four << std::endl;
	int const mangled = square(2e5);
	std::cout << "square(2e5) ~ " << mangled << std::endl;

	//*********************************************************
	// User-defined conversions
	//*********************************************************

	Int x = 1;     // Not a conversion, simply an initialization
	x.add(2);      // Convert 2 to Int using Int(int) constructor
	int y = x + 3; // Convert x to int to use int addition
	assert(y == 6);

	{
//		ExplicitInt x = 1; // ERROR - explicit constructor
//		x.add(2);          // ERROR - explicit constructor
//		int y = x + 3;     // ERROR - explicit conversion function
	}

	//*********************************************************
	// Ellipses conversions
	//*********************************************************

	printf("%d %c %s", 1, '1', "one");



	//*********************************************************
	// Explicit Conversion
	//*********************************************************
	Derived1 d;
	d.value_ = 42;
	Base & b = d;

	Derived1 & d1 = static_cast<Derived1&>(b); // OK - valid downcast
	assert(d1.value() == 42);
//	Derived2 & d2 = static_cast<Derived2&>(b); // UNDEFINED BEHAVIOR - invalid downcast
//	assert(d2.value() == 42);

	Derived1 * d1ptr = dynamic_cast<Derived1*>(&b); // OK
	assert(d1ptr != nullptr);
	Derived2 * d2ptr = dynamic_cast<Derived2*>(&b); // OK
	assert(d2ptr == nullptr);

	return 0;
}
