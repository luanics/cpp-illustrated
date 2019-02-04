#include "luanics/benchmark/Benchmark.hpp"
#include "luanics/benchmark/TableReporter.hpp"

#include "luanics/testing/Unit.hpp"

namespace luanics {
namespace benchmark {

BEGIN_TEST_SET(Benchmarker)

void subject(Benchmark & benchmark) {
	int const value = 42;
	while (benchmark.isRunning()) {
		std::vector<int> numbers;
		for (unsigned i = 0; i < benchmark.param(); ++i) {
			numbers.push_back(value);
		}
	}
	std::size_t numItemsProcessed = benchmark.totalNumIterations() * benchmark.param();
	std::size_t numBytesProcessed = numItemsProcessed * sizeof(int);
	benchmark.setNumItemsProcessed(numItemsProcessed);
	benchmark.setNumBytesProcessed(numBytesProcessed);
}

TEST(100x10) {
//	TableReporter reporter{&std::cout};
//
//	Benchmark benchmark{&reporter, "Vector", 100, 500, {1, 8, 64, 512, 1024}};
//	benchmark.run([](Benchmark & benchmark){
//		int const value = 42;
//		while (benchmark.isRunning()) {
//			std::vector<int> numbers;
//			for (unsigned i = 0; i < benchmark.param(); ++i) {
//				numbers.push_back(value);
//			}
//		}
//		std::size_t numItemsProcessed = benchmark.totalNumIterations() * benchmark.param();
//		std::size_t numBytesProcessed = numItemsProcessed * sizeof(int);
//		benchmark.setNumItemsProcessed(numItemsProcessed);
//		benchmark.setNumBytesProcessed(numBytesProcessed);
//	});

//	EXPECT_EQ(1, benchmark.results().size());
//	EXPECT_EQ(10, benchmark.results().back()._stats.count());
//	auto const & stats = benchmark.results().back()._stats;
//	std::cout << stats.mean() << " +/- " << stats.stdDev() << std::endl;
//
//	TableReporter reporter;
//	reporter.add(benchmark.results());
//	reporter.reportTo(std::cout);
}

END_TEST_SET(Benchmarker)

} // namespace container
} // namespace luanics
