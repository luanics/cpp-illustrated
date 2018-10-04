#include "luanics/testing/core/Composite.hpp"
#include "luanics/testing/tutorial/Instance.hpp"

namespace luanics::testing::tutorial {

core::Composite & tutorialInstance() {
	static core::Composite result{"Tutorial"};
	return result;
}
