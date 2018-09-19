#pragma once

#include <type_traits>

namespace luanics::testing::tutorial {

enum class Level : std::size_t {
	TUTORIAL = 0,
	PART = 1,
	CHAPTER = 2,
	SECTION = 3,
	TEST = 4
};

std::underlying_type_t<Level> toUnderlyingType(Level const & level);
/// @pre level < SECTION
Level & operator++(Level & level);
/// @pre level > TUTORIAL
Level & operator--(Level & level);

} // namespace luanics::testing::tutorial::level
