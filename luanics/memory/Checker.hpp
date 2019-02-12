#pragma once

#include <cstddef>
#include <iosfwd>

namespace luanics::memory {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class memory::Checker
///
/// @brief Keeps track of raw memory allocations and deallocations.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Checker {
public:
	Checker();
	~Checker();

	struct State;
	State const & state() const;

	void allocation(void * ptr, std::size_t const size);
	void deallocation(void * ptr);

	void reportTo(std::ostream & out);

	struct State {
		std::size_t bytesAllocated;
		std::size_t numAllocations;
		std::size_t numDeallocations;

		std::size_t netNumAllocations() const;
		bool operator==(State const & other) const;
		bool operator!=(State const & other) const;
	};

private:
	State _state;
};

std::ostream & operator<<(std::ostream & out, Checker::State const & s);

} // namespace luanics::memory
