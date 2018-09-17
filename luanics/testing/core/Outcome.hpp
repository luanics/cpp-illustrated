#pragma once

#include <iostream>

namespace luanics::testing::core {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Outcome
///
/// @brief A testing outcome.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
enum class Outcome {
	NONE, ///< All children have NONE outcome
	PASS, ///< At least one child has PASS outcome - beats NONE
	FAIL, ///< At least one child has FAIL outcome - beats PASS
	ERROR ///< At least one child has ERROR outcome - beats FAIL
};

Outcome combined(Outcome const lhs, Outcome const rhs);

std::ostream & operator<<(std::ostream & out, Outcome const outcome);

} // namespace luanics::testing::core
