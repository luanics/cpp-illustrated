#include "luanics/benchmarking/Benchmarker.hpp"
#include "luanics/benchmarking/Helpers.hpp"
#include "luanics/benchmarking/test/RecordingReporter.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::benchmarking {

BEGIN_TEST_SET(Benchmarker)

TEST(EmptyBenchmark) {
	RecordingReporter reporter;
	Benchmarker benchmark{&reporter, 30, 10000};
	benchmark.run("Empty", [](Benchmarker & benchmarker){
		while (benchmarker.isRunning()) {}
	});

	auto const position = reporter.resultsByLabel().find("Empty");
	EXPECT_TRUE(position != reporter.resultsByLabel().end());
	Result const & result = position->second;
	EXPECT_EQ(30, result.numSamples());
	EXPECT_EQ(10000, result.numIterationsPerSample());
	EXPECT_GT(0.1, secTotalFor(result));
}

TEST(100x10) {
//	TableReporter reporter{&std::cout};
//
//	Benchmark benchmarker{&reporter, "Vector", 100, 500, {1, 8, 64, 512, 1024}};
//	benchmarker.run([](Benchmark & benchmarker){
//		int const value = 42;
//		while (benchmarker.isRunning()) {
//			std::vector<int> numbers;
//			for (unsigned i = 0; i < benchmarker.param(); ++i) {
//				numbers.push_back(value);
//			}
//		}
//		std::size_t numItemsProcessed = benchmarker.totalNumIterations() * benchmarker.param();
//		std::size_t numBytesProcessed = numItemsProcessed * sizeof(int);
//		benchmarker.setNumItemsProcessed(numItemsProcessed);
//		benchmarker.setNumBytesProcessed(numBytesProcessed);
//	});

//	EXPECT_EQ(1, benchmarker.results().size());
//	EXPECT_EQ(10, benchmarker.results().back()._stats.count());
//	auto const & stats = benchmarker.results().back()._stats;
//	std::cout << stats.mean() << " +/- " << stats.stdDev() << std::endl;
//
//	TableReporter reporter;
//	reporter.add(benchmarker.results());
//	reporter.reportTo(std::cout);
}

END_TEST_SET(Benchmarker)

} // namespace luanics::benchmarking
