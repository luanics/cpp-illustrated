#include "luanics/testing/Unit.hpp"
#include "luanics/utility/ExpressionAnalysis.hpp"

namespace luanics {
namespace {

BEGIN_TEST_SET(ExpressionAnalysis)

TEST(Prvalue) {
	EXPECT_EQ(ValueCategory::PRVALUE, VALUE_CATEGORY_OF(2));
	EXPECT_TRUE((std::is_same<int, TYPE_OF(2)>::value));
	EXPECT_TRUE((
		std::is_same<ExpressionAnalysis<int, ValueCategory::PRVALUE>,
		ANALYSIS_OF(2)
	>::value));
	PRINT_ANALYSIS_OF(2);

	[[maybe_unused]] int x = 2;
	EXPECT_TRUE((std::is_same_v<
		ExpressionAnalysis<int, ValueCategory::PRVALUE>,
		ANALYSIS_OF(x+x)
	>));
	PRINT_ANALYSIS_OF(x+x);
}

TEST(Lvalue) {
	[[maybe_unused]] int x = 2;
	EXPECT_TRUE((std::is_same_v<
		ExpressionAnalysis<int, ValueCategory::LVALUE>,
		ANALYSIS_OF(x)
	>));

	[[maybe_unused]] float const y = 3.14;
	EXPECT_TRUE((std::is_same_v<
		ExpressionAnalysis<float const, ValueCategory::LVALUE>,
		ANALYSIS_OF(y)
	>));
}

TEST(Xvalue) {
	[[maybe_unused]] int x = 2;
	EXPECT_TRUE((std::is_same_v<
		ExpressionAnalysis<int, ValueCategory::XVALUE>,
		ANALYSIS_OF(std::move(x))
	>));
}

END_TEST_SET()

}
} // namespace luanics
