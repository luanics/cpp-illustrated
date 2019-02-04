#include "luanics/benchmarking/TableReporter.hpp"

#include <iostream>
#include "../../luanics/benchmarking/Benchmarker.hpp"

using namespace luanics::benchmark;

int main(int argc, char ** argv) {
	TableReporter reporter{&std::cout};

	constexpr int32_t numSteps = 64 * 1024 * 1024;
	constexpr int32_t cacheLineSize = 64;
	constexpr int32_t numInt32PerCacheLine = cacheLineSize / sizeof(int32_t); // = 16
	std::initializer_list<std::size_t> sizes{
		1 << 10,
		1 << 11,
		1 << 12,
		1 << 13,
		1 << 14,
		1 << 15,
		1 << 16,
		1 << 17,
		1 << 18,
		1 << 19,
		1 << 20,
		1 << 21,
		1 << 22,
		1 << 23,
		1 << 24
	};
	Benchmark benchmark{&reporter, "Cache", 1, 6, sizes, 1};
	benchmark.run([](Benchmark & benchmark){
		int32_t const sizeInBytes = benchmark.param();
		int32_t const numInts = sizeInBytes / sizeof(int32_t);
		int32_t * numbers = new int32_t[numInts];
		int32_t sizeMod = numInts - 1; // e.g., if array size is 8, sizeMod = 0b0111
		while (benchmark.isRunning()) {
			for (int32_t i = 0; i < numSteps; ++i) {
				++(numbers[(i * numInt32PerCacheLine) & sizeMod]);
			}
		}
		std::size_t numItemsProcessed = benchmark.totalNumIterations() * numSteps;
		benchmark.setNumItemsProcessed(numItemsProcessed);
	});

	return 0;
}
