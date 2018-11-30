#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cstdint>

constexpr int16_t WORK_HOURS_PER_DAY = 8;

//*********************************************************
// Basics
//*********************************************************

namespace basics {

void discipline(int8_t & breaksPerDay) {
	breaksPerDay -= 1;
}

void train(int16_t & linesPerHour) {
	linesPerHour += 10;
}

int16_t linesPerDay(
	int16_t const linesPerHour,
	int8_t const breaksPerDay
) {
	return linesPerHour * (WORK_HOURS_PER_DAY - breaksPerDay);
}

using SerialNumber = uint32_t;

SerialNumber topCoder(
	SerialNumber const coder1,
	int16_t const linesPerHour1,
	int8_t const breaksPerDay1,
	SerialNumber const coder2,
	int16_t const linesPerHour2,
	int8_t const breaksPerDay2
) {
	int16_t const linesPerDay1 = linesPerDay(linesPerHour1, breaksPerDay1);
	int16_t const linesPerDay2 = linesPerDay(linesPerHour2, breaksPerDay2);
	return linesPerDay1 > linesPerDay2 ? coder1 : coder2;
}

} // namespace basics

//*********************************************************
// Structures
//*********************************************************

namespace variables {

struct Coder {
	std::string name;
	uint32_t serialNumber;
	int16_t linesPerHour;
	int8_t breaksPerDay;
};

void discipline(Coder & coder) {
	coder.breaksPerDay -= 1;
}

void train(Coder & coder) {
	coder.linesPerHour += 10;
}

int16_t linesPerDay(Coder const & coder) {
	return coder.linesPerHour * (WORK_HOURS_PER_DAY - coder.breaksPerDay);
}

Coder const & topCoder(Coder const & a, Coder const & b) {
	return (linesPerDay(a) > linesPerDay(b)) ? a : b;
}

} // namespace variables

namespace functions {

struct Coder {
	void discipline() {breaksPerDay -= 1;}
	void train() {linesPerHour += 10;}
	int16_t linesPerDay() {
		return linesPerHour * (WORK_HOURS_PER_DAY - breaksPerDay);
	}

	std::string name;
	uint32_t serialNumber;
	int16_t linesPerHour;
	int8_t breaksPerDay;
};

} // namespace functions

//*********************************************************
// Access control
//*********************************************************

namespace access {

struct Coder {
public:
	void discipline() {breaksPerDay -= 1;}
	void train() {linesPerHour += 10;}
	int16_t linesPerDay() {
		return linesPerHour * (WORK_HOURS_PER_DAY - breaksPerDay);
	}
private:
	std::string name;
	uint32_t serialNumber;
	int16_t linesPerHour;
	int8_t breaksPerDay;
};

} // namespace access

//*********************************************************
// Constructors
//*********************************************************

namespace constructors {

struct Coder {
public:
	/// Parameterized constructor
	Coder(
		std::string const & name,
		uint32_t const serialNumber,
		int16_t const linesPerHour,
		int8_t const breaksPerDay
	) :
		_name{name},
		_serialNumber{serialNumber},
		_linesPerHour{linesPerHour},
		_breaksPerDay{breaksPerDay} {}
	/// Default constructor
	Coder() = default;

	std::string const & name() {return _name;}
	uint32_t serialNumber() {return _serialNumber;}
	int16_t linesPerHour() {return _linesPerHour;}
	int8_t breaksPerDay() {return _breaksPerDay;}

	void discipline() {_breaksPerDay -= 1;}
	void train() {_linesPerHour += 10;}
	int16_t linesPerDay() {
		return _linesPerHour * (WORK_HOURS_PER_DAY - _breaksPerDay);
	}

private:
	std::string _name;
	uint32_t _serialNumber;
	int16_t _linesPerHour;
	int8_t _breaksPerDay;
};

} // namespace constructors

//*********************************************************
// Constness
//*********************************************************

namespace constness {

struct Coder {
public:
	Coder(
		std::string const name,
		uint32_t const serialNumber,
		int16_t const linesPerHour,
		int8_t const breaksPerDay
	) :
		_name{name},
		_serialNumber{serialNumber},
		_linesPerHour{linesPerHour},
		_breaksPerDay{breaksPerDay} {}
	Coder() = default;

	std::string const & name() const {return _name;}
	uint32_t serialNumber() const {return _serialNumber;}
	int16_t linesPerHour() const {return _linesPerHour;}
	int8_t breaksPerDay() const {return _breaksPerDay;}

	void discipline() {_breaksPerDay -= 1;}
	void train() {_linesPerHour += 10;}
	int16_t linesPerDay() const {
		return _linesPerHour * (WORK_HOURS_PER_DAY - _breaksPerDay);
	}

private:
	std::string _name;
	uint32_t _serialNumber;
	int16_t _linesPerHour;
	int8_t _breaksPerDay;
};

} // namespace constness


int main() {
	luanics::utility::Herald herald{"Classes"};

	//*********************************************************
	// Basics
	//*********************************************************

	{
		using namespace basics;

		std::string stevesName = "Steve";
		uint32_t stevesSerialNumber = 10101;
		int16_t stevesLinesPerHour = 10;
		int8_t stevesBreaksPerDay = 2;

		std::string dylansName = "Dylan";
		uint32_t dylansSerialNumber = 10102;
		int16_t dylansLinesPerHour = 9;
		int8_t dylansBreaksPerDay = 1;

		SerialNumber const winner = topCoder(stevesSerialNumber, stevesLinesPerHour, stevesBreaksPerDay, dylansSerialNumber, dylansLinesPerHour, dylansBreaksPerDay);
		assert(winner == dylansSerialNumber);
	}

	//*********************************************************
	// Structures
	//*********************************************************

	{
		using namespace variables;
		Coder steve{"Steve", 10101, 10, 2}; // aggregate-initialized
		Coder dylan{"Dylan", 10102, 9, 1};
		Coder bibi{}; // value-initialized
		Coder fifi;   // default-initialized

		assert(dylan.breaksPerDay == 1);
		assert(bibi.linesPerHour == 0);

		Coder const & winner = topCoder(steve, dylan);
		assert(&winner == &dylan);
	}

	{
		using namespace functions;
		Coder dylan{"Dylan", 10102, 10, 1};
		assert(dylan.breaksPerDay == 1);
		dylan.discipline();
		assert(dylan.breaksPerDay == 0);
	}

	//*********************************************************
	// Access control
	//*********************************************************

	{
		using namespace functions;
		Coder dylan{"Dylan", 10102, 9, 1};
		assert(dylan.breaksPerDay == 1); // Hmm, Dylan needs some guidance ...
		dylan.discipline();
		assert(dylan.breaksPerDay == 0); // Good job, Dylan!
		dylan.breaksPerDay = 8; // Hey! That's cheating!
	}

	{
		using namespace access;
//		Coder  dylan{"Dylan", 10102, 9, 1}; // ERROR - no matching function!
		Coder fifi{}; // OK, but ...
//		assert(fifi.linesPerHour == 0); // ERROR - cannot access private member
	}

	//*********************************************************
	// Constructors
	//*********************************************************

	{
		using namespace constructors;
		Coder dylan{"Dylan", 10102, 9, 1}; // Parameterized constructor
		Coder fifi{}; // Default constructor
		assert(fifi.linesPerHour() == 0);
	}

	//*********************************************************
	// Constness
	//*********************************************************

	{
		using namespace constructors;
		Coder const fido{"Fido", 10103, 10, 1};
//		assert(fido.linesPerHour() == 10); // ERROR - linesPerHour() not const
	}

	{
		using namespace constness;
		Coder const fido{"Fido", 10103, 10, 1};
		assert(fido.linesPerHour() == 10); // OK
	}

	return 0;
}
