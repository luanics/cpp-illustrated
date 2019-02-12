#include "luanics/memory/Checker.hpp"
#include "luanics/testing/tutorial/Macros.hpp"

#include <cstdlib>

#ifdef LUANICS_LEAK_CHECKING

namespace luanics {
namespace memory {

Checker checker;

}
}

// This replacement for global new should
// 1) allocate memory using std::malloc
// 2) register the allocation with the luanics::memory::checker instance
// 3) return pointer to the allocated memory
void* operator new(std::size_t sz) {
	CREATE ANSWER(void * result = std::malloc(sz);
	luanics::memory::checker.allocation(result, sz);
	return result;
	)
}

// This replacement for global delete should
// 1) free memory using std::free
// 2) register the deallocation with the luanics::memory::checker instance
void operator delete(void * ptr) noexcept {
	CREATE ANSWER(luanics::memory::checker.deallocation(ptr);
	std::free(ptr);
	)
}

#endif
