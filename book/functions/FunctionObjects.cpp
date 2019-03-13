#include "luanics/utility/Herald.hpp"
#include "luanics/math/FloatingPoint.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

constexpr int add(int x, int y) {
	return x + y;
}

struct Add {
	constexpr int operator()(int x, int y) const {
		return x+ y;
	}
};

//*********************************************************
// Lambda capture
//*********************************************************

class Line {
public:
	Line(double m, double b) : _m{m}, _b{b} {}
	using Values = std::vector<double>;
	Values evaluatedAt(Values const & xs) {
		auto y = [this](int x){return _m * x + _b;};
		Values results;
		for (double x: xs) {
			results.push_back(y(x));
		}
		return results;
	}
private:
	double _m;
	double _b;
};


int main() {
	luanics::utility::Herald herald{"Function Objects"};

	constexpr auto addFunctionPtr = add;
	static_assert(addFunctionPtr(1,2) == 3);

	constexpr Add addCallableClass;
	static_assert(addCallableClass(1,2) == 3);

	auto addLambda = [](int x, int y){return x + y;};
	static_assert(addLambda(1,2) == 3);

	//*********************************************************
	// Lambda capture
	//*********************************************************

	{
		double m = 2.0;
		double b = -1.0;
		auto y = [m,b](int x){return m*x + b;};
		assert(luanics::areClose(-1.0, y(0)));
		assert(luanics::areClose(1.0, y(1)));
	}

	{
		int total = 0;
		assert(total == 0);
		auto addToTotal = [&total](int x){total += x;};
		addToTotal(10);
		assert(total == 10);
	}

	{
		int x = 1;
	//	auto badIncrement = [x](){x += 1;};
		auto goodIncrement = [&x](){x += 1;};
		assert(x == 1);
		goodIncrement();
		assert(x == 2);
	}

	{
		double m = 2.0;
		double b = -1.0;
		auto y = [=](int x){return m*x + b;}; // implicitly capture m & b
		assert(luanics::areClose(-1.0, y(0)));
		assert(luanics::areClose(1.0, y(1)));

		int total = 0;
		assert(total == 0);
		auto addToTotal = [&](int x){total += x;}; // implicitly capture total
		addToTotal(10);
		assert(total == 10);
	}

	//*********************************************************
	// Object capture
	//*********************************************************

	{
		Line line{2.0, -1.0};
		Line::Values const xs{0.0, 1.0, 2.0};
		auto const ys = line.evaluatedAt(xs);
		Line::Values const expectedYs{-1.0, 1.0, 3.0};
		assert(luanics::areAllClose(expectedYs, ys));
	}

	//*********************************************************
	// Generalized lambda capture
	//*********************************************************

	{
		std::string firstName = "Zoinkie";
		std::string lastName = "Zoinkers";
		auto say = [name = firstName + " " + lastName](std::string const & message){
			std::cout << message << " " << name << std::endl;
		};
		say("Hi");
		say("Goodbye");

		std::string introduction = "Oh my ";
		auto exclaim = [intro = std::move(introduction)](std::string const & target){
			std::cout << intro << target << '!' << std::endl;
		};
		exclaim("Zoinks");
		exclaim("Carrots");
	}

	//*********************************************************
	// Generic lambda
	//*********************************************************

	auto doubled = [](auto x){return x + x;};
	assert(doubled(2) == 4);
	assert(doubled(std::string{"halo"}) == std::string{"halohalo"});

	//*********************************************************
	// std::function
	//*********************************************************

	std::function<int(int,int)> const adder1 = addCallableClass;
	std::function<int(int,int)> const adder2 = add;
	std::function<int(int,int)> const adder3 = [](int x, int y){return x + y;};

	return 0;
}
