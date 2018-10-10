#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>

//*********************************************************
// class Dog
//*********************************************************

class Dog {
public:
	Dog();
	Dog(std::string name);
	std::string const & name() const;
	unsigned numTricks() const;
	void learnNewTricks();

private:
	std::string _name;
	unsigned _numTricks;
}; // class Dog

Dog::Dog() :
	_name{}, _numTricks{0}
{}

Dog::Dog(std::string name) :
	_name{std::move(name)}, _numTricks{0}
{}

std::string const & Dog::name() const {
	return _name;
}

unsigned Dog::numTricks() const {
	return _numTricks;
}

void Dog::learnNewTricks() {
	++_numTricks;
}

//*********************************************************
// struct Int
//*********************************************************

struct Int {
	explicit Int(int value) : _value{value} {}
	int _value;
};

//*********************************************************
// class Database
//*********************************************************

class Database {
public:
	void open() {}
	int query(std::string const & target) {return 4;}
}; // class Database


//*********************************************************
// Main
//*********************************************************

struct X {
	X(int) {}
	X(X const &) = delete;
};

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Variables"};

	X z = X{1};
	//*********************************************************
	// Basics
	//*********************************************************

	Dog fidus;                 // Dog, fidus, NA
	Dog & fido = fidus;        // Dog &, fido, =fidus
	float wagsPerSecond{4.3};  // float, wagsPerSecond, {4.3}
	int years = 5;             // int, years, =5
	int & age = years;         // int &, age, =years

	assert(age == 5);
	years = 6;
	assert(age == 6);
	age = 7;
	assert(years == 7);

	float x;
//	x = 2 * y; // ERROR - y not defined
	float y;
	x = 2 * y; // OK

	float bonesPerYard = 21.8, goldenRatio = 1.62;

	//*********************************************************
	// Constness
	//*********************************************************

	Dog const hound;
//	const Dog hound;

	Dog const oldDog{"Yeller"}; // OK - initialization allowed on const
	Dog newDog{"Fifi"}; // ERROR - initialization allowed on non-const
//	oldDog = newDog; // ERROR - can't assign to const object
	std::string oldDogName = oldDog.name(); // OK - not changing state
//	oldDog.learnNewTricks(); // ERROR - can't call non-const method on const object

	float const pi = 3.14;
//	pi = 3.00e8; // ERROR - cannot assign to read-only variable

	//*********************************************************
	// Constexpr variables
	//*********************************************************

	float constexpr pi2 = 3.14; // Better
	constexpr float pi3 = 3.14; // Also OK

	//*********************************************************
	// Type Deduction
	//*********************************************************

	auto number = 1;     // OK - compiler deduces type int from 1
	auto name = "Gengi"; // OK - compiler deduces type string from "Gengi"
//	auto x;              // ERROR - can't deduce type without initializer

	auto const morePi = 3.14;        // Type of morePi is "float const"
	auto const & anotherPi = morePi; // Type of anotherPi is "float const &"

	//*********************************************************
	// Initialization
	//*********************************************************

//	float pi;   // definition (oops, can't make const)
//	pi = 3.14;  // assignment
//	float const pi = 3.14; // definition with initializer

	int a;       // without initializer -> default

	int b{1}; // with braces -> list initialization
	int c(1); // without braces -> no-list initialization

	int d(1.0);    // OK
//	int e{1.0};    // ERROR - narrowing conversion
	int f = 1.0;   // OK
//	int g = {1.0}; // ERROR - narrowing conversion

	int h = 1; // with equal sign -> copy initialization
	int i{2};  // without equal sign -> direct initialization

	Int j{1};  // OK - direct initialization
//	Int k = 1; // ERROR - copy initialization

//	int l();    // INCORRECT - empty no-list direct, not initialization!
//	int m = (); // ERROR - empty no-list copy, not allowed!
	int n{};    // OK - empty list direct
	int o = {}; // OK - empty list copy

	//*********************************************************
	// Reference Variable Initialization
	//*********************************************************

	int & p{n};  // OK - direct initialization
	int & q = o; // OK - copy initialization
//	int & r;     // ERROR - default initialization
//	int & s{};   // ERROR - value initialization

	char t{};
//	int & u = t; // ERROR - type mismatch

	//*********************************************************
	// Uninitialized Variables
	//*********************************************************

	int numFleas{};        // Value initialization - zeroed
	// or
	int dogAgeInYears = 0; // Copy initialization - zeroed
	// but not
	int bonesPerSecond;    // Default initialization - could be anything!

//	int numClaws;
//	Database database;
//	database.open();
//	numClaws = database.query("cat.num_claws");
	Database database;
	database.open();
	int const numClaws = database.query("cat.num_claws");

	return 0;
}
