#include "luanics/memory/Checker.hpp"
#include "luanics/utility/Streams.hpp"

#include <iostream>
#include <locale>

namespace luanics::memory {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Checker Implementation
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Checker::Checker() : _state{} {}

Checker::~Checker() {
	reportTo(std::cout);
}

Checker::State const & Checker::state() const {
	return _state;
}

void Checker::allocation(void * ptr, std::size_t const size) {
	_state.bytesAllocated += size;
	++_state.numAllocations;
}

void Checker::deallocation(void * ptr) {
	++_state.numDeallocations;
}

void Checker::reportTo(std::ostream & out) {
	using namespace utility::streams;
	out << plain;
	bool const isBalanced = _state.numAllocations == _state.numDeallocations;
	out << boldGreen << "[==========]" << plain << std::endl;
	out << boldGreen << "[" << boldBlue << "  MEMORY  " << boldGreen << "]" << plain << std::endl;
	out << boldGreen << "[==========]" << plain << std::endl;
	if (isBalanced) {
		out << boldGreen << "[  PASSED  ] " << plain;
	}
	else {
		out << boldRed << "[  FAILED  ] " << plain;
	}
	// imbue/locale will use "new" and "delete", so save before going further.
	auto currentState = _state;
//	std::locale oldLocale = out.imbue(std::locale(""));
	out << currentState << std::endl;
//	out.imbue(oldLocale);
	out << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Checker::State Implementation
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool Checker::State::operator==(State const & other) const {
	return
		bytesAllocated == other.bytesAllocated
		and numAllocations == other.numAllocations
		and numDeallocations == other.numDeallocations;
}

bool Checker::State::operator!=(State const & other) const {
	return not operator==(other);
}

std::size_t Checker::State::netNumAllocations() const {
	return numAllocations - numDeallocations;
}

std::ostream & operator<<(std::ostream & out, Checker::State const & s) {
	out << "(";
	out << "bytes=" << s.bytesAllocated << ", ";
	out << "allocs=" << s.numAllocations << ", ";
	out << "deallocs=" << s.numDeallocations;
	out << ")";
	return out;
}

} // namespace luanics::checker
