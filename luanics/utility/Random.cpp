#include "luanics/utility/Random.hpp"

#include <random>

namespace luanics {

unsigned randomSeed() {
	static std::random_device device;
	return device();
}

} // namespace luanics
