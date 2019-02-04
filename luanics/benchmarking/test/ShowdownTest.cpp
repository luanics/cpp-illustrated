#include "luanics/benchmarking/Showdown.hpp"
#include "luanics/testing/Unit.hpp"

#include <cmath>
#include <chrono>
#include <thread>

using namespace luanics::testing;

namespace luanics {
namespace benchmarking {

BEGIN_TEST_SET(Showdown)

TEST(Tie) {
	auto challenger = []{std::this_thread::sleep_for(std::chrono::microseconds(50));};
	auto defender = []{std::this_thread::sleep_for(std::chrono::microseconds(50));};
	Showdown showdown{challenger, defender, 10, 100, false};
	EXPECT_EQ(Winner::TIE, showdown.winner());
}

TEST(ChallengerWins) {
	auto challenger = []{};
	auto defender = []{std::this_thread::sleep_for(std::chrono::microseconds(1));};
	Showdown showdown{challenger, defender, 10, 100, false};
	EXPECT_EQ(Winner::CHALLENGER, showdown.winner());
}

TEST(DefenderWins) {
	auto challenger= []{std::this_thread::sleep_for(std::chrono::microseconds(1));};
	auto defender = []{};
	Showdown showdown{challenger, defender, 10, 100, false};
	EXPECT_EQ(Winner::DEFENDER, showdown.winner());
}

END_TEST_SET(Showdown)

} // namespace benchmarking
} // namespace luanics
