#include "luanics/utility/Herald.hpp"
#include "luanics/utility/Orator.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

//*********************************************************
// Construction
//*********************************************************

class Person {
public:
	////////////////////////////////////////////////////////
	/// @name Construction
	////////////////////////////////////////////////////////
	//@{
	/// Default constructor
	Person();
	/// Parameterized constructor
	Person(std::string const & name, unsigned const age);
	/// Copy constructor
	Person(Person const & other);
	/// Move constructor
	Person(Person && other);
	//@}

	////////////////////////////////////////////////////////
	/// @name Assignment
	////////////////////////////////////////////////////////
	//@{
	/// Copy assignment
	Person & operator=(Person const & other);
	/// Move assignment
	Person & operator=(Person && other);
	//@}

	////////////////////////////////////////////////////////
	/// @name Destruction
	////////////////////////////////////////////////////////
	//@{
	/// Destructor
	~Person();
	//@}

	bool isAnonymous() const {return _name.empty();}
	std::string const & name() const {return _name;}
	unsigned age() const {return _age;}

private:
	std::string _name;
	unsigned _age;
};
// class Person

// default constructor implementation
Person::Person()
	: _name{}, _age{}
{}

// parameterized constructor implementation
Person::Person(std::string const & name, unsigned const age)
	: _name{name}, _age{age}
{}

// copy constructor implementation
Person::Person(Person const & other)
	: _name{other._name}, _age{other._age}
{}

// move constructor implementation
Person::Person(Person && other)
	: _name{std::move(other._name)}, _age{other._age}
{other._age = 0;}

//*********************************************************
// Construction Categories
//*********************************************************

class Array {
public:
	static constexpr std::size_t CapacityValue = 100;
	using ValueType = int;

	/// Construct Array from initializer list values
	Array(std::initializer_list<ValueType> values);

	ValueType front() const {return _data[0];}
	ValueType back() const {return _data[_size-1];}
	std::size_t size() const {return _size;}
	std::size_t capacity() const {return CapacityValue;}

private:
	int _start;
	int _size;
	int _data[CapacityValue];
};

Array::Array(std::initializer_list<ValueType> values) :
	_start{0}, _size{0}, _data{}
{
	std::size_t size = std::min(capacity(), values.size());
	std::copy(std::begin(values), std::begin(values) + size, std::begin(_data));
	_size = size;
}

//*********************************************************
// Member initialization
//*********************************************************

struct FullName {
	FullName() = default;
	FullName(std::string const & first) : _first{first} {
		assert(_last == "Bond");
	}

	std::string _first{"James"}; // default member initializer
	std::string _last{"Bond"};   // default member initializer
};

struct BadName {
	BadName(std::string const & first, std::string const & last) :
		_first{first}, _last{last}, _full{_first + " " + _last} // UB
	{}

	std::string _full; // :(
	std::string _first;
	std::string _last;
};

struct GoodName {
	GoodName(std::string const & first, std::string const & last) :
		_first{first}, _last{last}, _full{_first + " " + _last} // OK
	{}

	std::string _first;
	std::string _last;
	std::string _full; // :)
};

//*********************************************************
// Delegating constructors
//*********************************************************

class Array2 {
public:
	static constexpr std::size_t CapacityValue = 100;
	using ValueType = int;

	Array2() : _start{0}, _size{0}, _data{} {} // default constructor
	Array2(std::initializer_list<ValueType> values);

	ValueType front() const {return _data[0];}
	ValueType back() const {return _data[_size-1];}
	std::size_t size() const {return _size;}
	std::size_t capacity() const {return CapacityValue;}

private:
	int _start;
	int _size;
	int _data[CapacityValue];
};

Array2::Array2(std::initializer_list<ValueType> values) :
	Array2() // target constructor
{
	std::size_t size = std::min(capacity(), values.size());
	std::copy(std::begin(values), std::begin(values) + size, std::begin(_data));
	_size = size;
}

//*********************************************************
// Assignment
//*********************************************************

// copy assignment implementation
Person & Person::operator=(Person const & other) {
	_name = other._name;
	_age = other._age;
	return *this;
}

// move assignment implementation
Person & Person::operator=(Person && other) {
	_name = std::move(other._name);
	_age = other._age;
	return *this;
}

//*********************************************************
// Destruction
//*********************************************************

Person::~Person() {}

//*********************************************************
// Defaulted methods
//*********************************************************

class Empty {};

class AlsoEmpty {
public:
	AlsoEmpty() = default;
	AlsoEmpty(AlsoEmpty const & other) = default;
	AlsoEmpty & operator=(AlsoEmpty const & other) = default;
	AlsoEmpty(AlsoEmpty && other) = default;
	AlsoEmpty & operator=(AlsoEmpty && other) = default;
	~AlsoEmpty() = default;
};

class ImplicitlyDefaulted {
private:
	std::string _name;
	int _number;
};

class ExplicitlyDefaulted {
	ExplicitlyDefaulted() = default;
	ExplicitlyDefaulted(ExplicitlyDefaulted const &) = default;
	ExplicitlyDefaulted(ExplicitlyDefaulted &&) = default;
	ExplicitlyDefaulted & operator=(ExplicitlyDefaulted const &) = default;
	ExplicitlyDefaulted & operator=(ExplicitlyDefaulted &&) = default;
private:
	std::string _name;
	int _number;
};

class Explicit {
public:
	Explicit() :
		_name{}, _number{} {}
	Explicit(Explicit const & other) :
		_name{other._name}, _number{other._number} {}
	Explicit & operator=(Explicit const & other) {
		_name = other._name;
		_number = other._number;
		return *this;
	}
	Explicit(Explicit && other) :
		_name{std::move(other._name)}, _number{std::move(other._number)} {}
	Explicit & operator=(Explicit && other) {
		_name = std::move(other._name);
		_number = std::move(other._number);
		return *this;
	};
private:
	std::string _name;
	int _number;
};

//*********************************************************
// Deleted methods
//*********************************************************

class Uncopyable {
public:
	Uncopyable() = default;
	Uncopyable(Uncopyable const & other) = delete;
	Uncopyable(Uncopyable && other) = default;
	Uncopyable & operator=(Uncopyable const & other) = delete;
	Uncopyable & operator=(Uncopyable && other) = default;
};

//*********************************************************
// Named constructors
//*********************************************************

class Color {
public:
	using ValueType = uint8_t;
	static Color fromRgb(ValueType const red, ValueType const green, ValueType const blue);
	static Color fromCmy(ValueType const cyan, ValueType const magenta, ValueType const yellow);

private:
	Color(ValueType const red, ValueType const green, ValueType const blue);
	ValueType _red;
	ValueType _green;
	ValueType _blue;
};

Color::Color(ValueType const red, ValueType const green, ValueType const blue) :
	_red{red}, _green{green}, _blue{blue}
{}

Color Color::fromRgb(ValueType const red, ValueType const green, ValueType const blue) {
	return Color{red, green, blue};
}

Color Color::fromCmy(ValueType const cyan, ValueType const magenta, ValueType const yellow) {
	ValueType const red = 255 - cyan;
	ValueType const green = 255 - magenta;
	ValueType const blue = 255 - yellow;
	return Color{red, green, blue};
}

//*********************************************************
// Copy elision
//*********************************************************

namespace luanics::utility {

Orator makeOrator() {
	Orator result{};
	return result;
}

}

//*******************************************************************
// Main
//*******************************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"ManagementMethods"};

	//*********************************************************
	// Basics
	//*********************************************************

	{
	Person a;    // a constructed
	{
		Person b; // b constructed
		a = b;    // b assigned to a
	}            // b destructed
	}

	//*********************************************************
	// Construction
	//*********************************************************

	{
	Person anon; // default constructor
	assert(anon.isAnonymous());
	assert(anon.name() == ""); // anon has no name
	Person nameless{}; // also default constructor
	assert(nameless.isAnonymous());
	Person jane{"Jane", 50}; // parameterized constructor
	assert(jane.name() == "Jane");
	Person alsoJane{jane}; // copy constructor via "direct initialization"
	assert(alsoJane.name() == "Jane");
	Person janeToo = jane; // copy constructor via "copy initialization"
	Person identityThief{std::move(jane)}; // move constructor
	assert(identityThief.name() == "Jane");
	assert(jane.isAnonymous());
	}

	//*********************************************************
	// Construction Categories
	//*********************************************************

	{
		Array array{1,2,3};
		assert(array.size() == 3);
		assert(array.front() == 1);
		assert(array.back() == 3);
	}

	//*********************************************************
	// Member initialization
	//*********************************************************

	FullName jamesBond;
	assert(jamesBond._first == "James");
	assert(jamesBond._last == "Bond");
	FullName janeBond{"Jane"};
	assert(janeBond._first == "Jane");
	assert(janeBond._last == "Bond");

	//*********************************************************
	// Move versus copy
	//*********************************************************
	{
		Person jane{"Jane", 50};
		assert(jane.name() == "Jane");
		Person alsoJane{jane}; // copy constructor
		assert(jane.name() == "Jane");
		assert(alsoJane.name() == "Jane");
		Person identityThief{std::move(jane)}; // move constructor
		assert(jane.name() == "");
		assert(identityThief.name() == "Jane");
	}

	//*********************************************************
	// Assignment
	//*********************************************************

	{
		Person john{"John", 15};
		assert(john.name() == "John");
		Person johnClone;
		johnClone = john; // copy assignment
		assert(johnClone.name() == "John");
		Person johnTransplant;
		johnTransplant = std::move(john); // move assignment
		assert(john.name() == "");
		assert(johnTransplant.name() == "John");
	}

	//*********************************************************
	// Defaulted methods
	//*********************************************************

	{
		Empty empty; // call default constructor
		Empty vacuum{empty}; // call copy constructor
		Empty lacuna;
		lacuna = empty; // call copy assignment
		Empty space{std::move(lacuna)}; // call move constructor
		Empty nothingness;
		nothingness = std::move(space); // call move assignment
	} // call all destructors as leave scope

	//*********************************************************
	// Deleted methods
	//*********************************************************

	{
		Uncopyable stubborn;
//		Uncopyable obstinate{stubborn}; // ERROR - can't copy
		Uncopyable hardheaded{std::move(stubborn)}; // OK - can move
	}

	//*********************************************************
	// Named constructors
	//*********************************************************

	{
		Color red = Color::fromRgb(255, 0, 0);
		Color alsoRed = Color::fromCmy(0, 255, 255);
	}

	//*********************************************************
	// Access control
	//*********************************************************

	{
//		Color maybeRed{255, 0, 0}; // ERROR - private
	}

	//*********************************************************
	// Copy elision
	//*********************************************************

	{
		using namespace luanics::utility;
		Orator o = makeOrator();
	}

	return 0;
}
