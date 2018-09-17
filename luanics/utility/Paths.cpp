#include "luanics/utility/Paths.hpp"

#include <cstring>

namespace luanics::utility {

char const * fileNameFrom(char const * const pathName, char const delimiter) {
	auto found = std::strrchr(pathName, delimiter);
	return found == nullptr ? pathName : found + 1;
}

} // namespace luanics::utility
