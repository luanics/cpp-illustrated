#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <complex>
#include <iostream>
#include <cstdint>
#include <ios>

struct Coder1 {
	char const * name;
	uint32_t serialNumber;
	int16_t linesPerHour;
	int8_t breaksPerDay;
};

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Operators"};

	//*********************************************************
	// Basics
	//*********************************************************

	std::complex<double> ac = 1.0;
	std::complex<double> bc = 2.0;
	std::complex<double> cc = ac + bc; // OK
	std::complex<double> dc = operator+(ac, bc); // OK
	assert(cc == dc);

	int ai = 1;
	int bi = 2;
	int ci = ai + bi; // OK
//	int di = operator+(ai, bi); ERROR
	assert(ci == 3);

	//*********************************************************
	// Precedence
	//*********************************************************

	int const x = 2;
	int const y = 1;
	int const z = 3*x - 2*y;
	assert(z == 4);
	int const zParens = ( ( (3) * (x) ) - ( (2) * (y) ) );
	assert(zParens == 4);
	//*******************************************************************
	// Logical operators
	//*******************************************************************
	bool b1{false};
	bool b2{true};
	assert((b1 && b2) == false);
	assert((b1 || b2) == true);
	assert(!b1 == b2);

	//*******************************************************************
	// Bitwise Logical and shift operators
	//*******************************************************************
	uint8_t const x1 = 0b11110000;
	uint8_t const y1 = 0b10101010;
	uint8_t const z1 = x1 & y1;
	assert(z1==0b10100000);
	uint8_t xs1 = (x1<<2);
	assert(xs1 == 0b11000000);

	//*******************************************************************
	// Comparison operators
	//*******************************************************************
	int v1 = 1;
	int v2 = 2;
	int v3 = 3;
	assert(v1 < v2 < v3);  	// OK
	assert(v2 < v1 < v3);   // Also OK!

	assert(false < true);
	// assert(true < false);
	int tryThis = 2;
	assert(true < tryThis);
	int x2 = 3;
	int y2 = 4;
	int z2 = 5;
//	assert(x2<y2<z2);
//	assert(y2<z2<x2);
//	assert(false < x2);
//	assert(y2<x2<z2);

	//*******************************************************************
	// Arithmetic operators
	//*******************************************************************
	uint_least16_t xyy = 170;
	uint_least16_t pqq = -xyy;
	assert(pqq==65366);
	int_least16_t xyz = 170;
	int_least16_t pqr = -xyz;
	assert(pqr==-170);

	int q = 3;
	int r = 7;
	assert(q*r==21);
	assert(r/q==2);
	assert(r%q==1);

	int a = 12;
	int b = 6;
	assert(a+b==18);
	assert(a-b==6);

	//*******************************************************************
	// Postfix Increment and Decrement
	//*******************************************************************
	int j = 1;
	int k = j++;
	assert(k==1);
	assert(j==2);
	int l = j--;
	assert(j==1);
	assert(l==2);
	//*******************************************************************
	// Address-of operator
	//*******************************************************************
	int pop = 2;
	int * add = &pop;
	assert(*add == 2);
	//*******************************************************************
	// Assignment operators
	//*******************************************************************

	int t = 7;
	int u = t += 7;
	assert(t==14);
	assert(u==14);
	//*******************************************************************
	// Prefix increment and decrement
	//*******************************************************************
	int catsup = 57;
	int notCatsup = --catsup;
	assert(notCatsup==56);
	//*******************************************************************
	// dereference operator
	//*******************************************************************

	int val = 23;
	int* ptr = &val;
	assert(*ptr==23);

	//*******************************************************************
	// subscript operator
	//*******************************************************************
	int data[] = {4, 5, 6};
	assert(data[0]==4);

	//*******************************************************************
	// member access operators
	//*******************************************************************
	Coder1 john{"John", 10101, 100, 2};
	std::cout << john.serialNumber << std::endl;
	Coder1 * peterson = &john;
	std::cout << peterson->serialNumber << std::endl;


	return 0;
}
