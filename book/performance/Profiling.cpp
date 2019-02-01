#include "luanics/profiling/Profiling.hpp"
#include "luanics/utility/Herald.hpp"

#include <numeric>
#include <cstdlib>
#include <vector>

int generateRandom() {
	PROFILE_FUNCTION()
	return std::rand() % 100;
}

bool isLarge(int const value) {
	PROFILE_FUNCTION()
	return value > 50 ? true : false;
}

std::vector<int> generateRandoms() {
	PROFILE_FUNCTION()
	std::vector<int> randoms;
	for (int i = 0; i < 1000; ++i) {
		randoms.push_back(std::rand() % 100);
	}
	return randoms;
}

int sumRandoms(std::vector<int> const & randoms) {
	PROFILE_FUNCTION()
	return std::accumulate(randoms.begin(), randoms.end(), 0);
}

int main() {
	luanics::utility::Herald herald{"profiling"};
	PROFILE_BEGIN()

	for (int i = 0; i < 1000; ++i) {
		auto randoms = generateRandoms();
		auto sum = sumRandoms(randoms);
	}

	PROFILE_END()
	PROFILE_REPORT(std::cout);
	return 0;
}
