#include "luanics/logging/Contract.hpp"
#include "luanics/testing/tutorial/Level.hpp"

namespace luanics::testing::tutorial {

std::underlying_type_t<Level> toUnderlyingType(Level const & level) {
	return static_cast<std::underlying_type_t<Level>>(level);
}

Level & operator++(Level & level) {
	LUANICS_PRECONDITION(toUnderlyingType(level) < toUnderlyingType(Level::TEST));
	level = static_cast<Level>(toUnderlyingType(level) + 1);
	return level;
}

Level & operator--(Level & level) {
	LUANICS_PRECONDITION(toUnderlyingType(level) > toUnderlyingType(Level::TUTORIAL));
	level = static_cast<Level>(toUnderlyingType(level) - 1);
	return level;
}

} // namespace luanics::testing::tutorial
