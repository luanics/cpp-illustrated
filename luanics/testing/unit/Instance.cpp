#include "luanics/testing/unit/Instance.hpp"

namespace luanics::testing::unit {

core::Composite & suiteInstance() {
	static core::Composite instance{"Suite"};
	return instance;
}

} // namespace luanics::testing::core
