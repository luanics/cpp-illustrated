#pragma once

#include <cstddef>

namespace luanics::testing::unit {

enum class Level : std::size_t {
	SUITE = 0,
	SET = 1,
	TEST = 2
};

} // namespace luanics::testing::unit
