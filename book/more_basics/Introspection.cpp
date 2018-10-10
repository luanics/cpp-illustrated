#include <cassert>
#include <iostream>
#include <limits>

int main(int argc, char ** argv) {

	//*********************************************************
	// static_assert
	//*********************************************************

	bool constexpr arePigsFlying = false;
	assert(not arePigsFlying);         // Fail at run-time
	static_assert(not arePigsFlying);  // Fail at compile-time

	bool constexpr isSkyFalling = true;
	static_assert(isSkyFalling);
	bool const isFlyCalling = true;
//	static_assert(isFlyCalling); // ERROR - isFlyCalling not constexpr

	bool constexpr isSunRisingInWest = false;
	bool constexpr isCrowTurningWhite = false;
	static_assert(not isSunRisingInWest and not isCrowTurningWhite);

	//*********************************************************
	// Numeric Limits
	//*********************************************************

	std::cout << "unsigned: ["
		<< std::numeric_limits<unsigned>::lowest() << ","
		<< std::numeric_limits<unsigned>::max() << "]" << std::endl;
	std::cout << "int: ["
		<< std::numeric_limits<int>::lowest() << ","
		<< std::numeric_limits<int>::max() << "]" << std::endl;
	std::cout << "float: ["
		<< std::numeric_limits<float>::lowest() << ","
		<< std::numeric_limits<float>::max() << "]" << std::endl;

	//*********************************************************
	// Type Traits
	//*********************************************************

	assert(std::is_arithmetic<int>::value); // long form
	assert(std::is_arithmetic_v<int>);      // short form

	assert(not std::is_class<int>::value);  // long form
	assert(not std::is_class_v<int>);       // short form

	static_assert(not std::is_class_v<int>);
	static_assert(not std::is_const_v<int>);
	static_assert(std::is_arithmetic_v<int>);
	static_assert(not std::is_same_v<int, char>);
	static_assert(std::is_same_v<int, int>);

	class Dog {};
	static_assert(std::is_class_v<Dog const>);
	static_assert(std::is_const_v<Dog const>);
	static_assert(not std::is_arithmetic_v<Dog const>);

	static_assert(not std::is_same_v<char, unsigned char>);
	static_assert(not std::is_same_v<unsigned char, signed char>);
	static_assert(not std::is_same_v<signed char, char>);

	// Type Category Queries
	static_assert(std::is_fundamental_v<int>);
	static_assert(std::is_compound_v<int &>);
	static_assert(std::is_integral_v<int>);
	static_assert(std::is_class_v<std::string>);
	static_assert(std::is_function_v<int(int)>);
	static_assert(std::is_object_v<int>);
	static_assert(std::is_reference_v<int &>);
	static_assert(std::is_arithmetic_v<int>);

	// Type Property Queries
	static_assert(std::is_const_v<int const>);
	static_assert(std::is_signed_v<int>);
	static_assert(std::is_unsigned_v<unsigned int>);

	// Type Relationship Queries
	static_assert(not std::is_same_v<int,float>);
	static_assert(not std::is_base_of_v<int,float>);
	static_assert(std::is_convertible_v<int,float>);

	//*********************************************************
	// decltype
	//*********************************************************

	int x;

	static_assert(std::is_same_v<int, decltype(x)>);

	static_assert(std::is_same_v<decltype(x),int>);
	static_assert(std::is_same_v<decltype((x)),int &>);

	//*********************************************************
	// declval
	//*********************************************************

	class T {
	public:
		T() = delete;
		T(int value) : _value{value} {}
		int method() {return _value;}
	private:
		int _value;
	};

	using ReturnType = decltype(std::declval<T>().method());
	T t{1};
	ReturnType returnValue = t.method();

	return 0;
}
