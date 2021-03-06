#include "luanics/benchmarking/TableReporter.hpp"

#include "luanics/benchmarking/Helpers.hpp"
#include "luanics/benchmarking/Result.hpp"
#include "luanics/utility/Streams.hpp"

#include <iomanip>

namespace luanics::benchmarking {

constexpr unsigned LABEL_COLUMN_WIDTH = 20;
constexpr unsigned NUM_SAMPLES_COLUMN_WIDTH = 12;
constexpr unsigned NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH = 12;
constexpr unsigned TOTAL_TIME_COLUMN_WIDTH = 12;
constexpr unsigned MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH = 12;
constexpr unsigned MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH = 10;
constexpr unsigned NSEC_PER_ITEM_MEAN_COLUMN_WIDTH = 12;
constexpr unsigned ITEMS_PER_SAMPLE_COLUMN_WIDTH = 12;
constexpr unsigned ITEMS_PER_SEC_COLUMN_WIDTH = 12;
constexpr unsigned TOTAL_WIDTH =
	LABEL_COLUMN_WIDTH
	+ NUM_SAMPLES_COLUMN_WIDTH
	+ NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH
	+ TOTAL_TIME_COLUMN_WIDTH
	+ MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH
	+ MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH
	+ NSEC_PER_ITEM_MEAN_COLUMN_WIDTH
	+ ITEMS_PER_SEC_COLUMN_WIDTH
;

TableReporter::TableReporter(std::ostream * out) : _out{out} {
	printHeader();
}

void TableReporter::report(Result const & result) {
	using namespace utility::streams;
	out() << green << std::left << std::setw(LABEL_COLUMN_WIDTH) << result.label();
	out() << cyan << std::right << std::setw(NUM_SAMPLES_COLUMN_WIDTH) << std::fixed << std::setprecision(0) << result.numSamples();
	out() << cyan << std::right << std::setw(NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH) << std::fixed << std::setprecision(0) << result.numIterationsPerSample();
	out() << brown << std::right << std::setw(TOTAL_TIME_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << secTotalFor(result);
	out() << white << std::right << std::setw(MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << msecPerSampleMeanFor(result);
	out() << darkGray << std::right << std::setw(MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << msecPerSampleStdDevFor(result);
	if (result.hasNumItemsProcessed()) {
		out() << white << std::right << std::setw(NSEC_PER_ITEM_MEAN_COLUMN_WIDTH) << std::fixed << std::setprecision(1) << nsecPerItemMeanFor(result);
		double const megaItemsPerSecond = itemsPerSecFor(result) * 1.0e-6;
		out() << white << std::right << std::setw(ITEMS_PER_SEC_COLUMN_WIDTH) << std::fixed << std::setprecision(2) << megaItemsPerSecond;
	}
	else {
		out() << std::string(ITEMS_PER_SEC_COLUMN_WIDTH, ' ');
	}
	out() << plain << "\n";
	out().flush();
}

std::ostream & TableReporter::out() {return *_out;}

void TableReporter::printHeader() {
	out() << std::left << std::setw(LABEL_COLUMN_WIDTH) << "Benchmark";
	out() << std::right << std::setw(NUM_SAMPLES_COLUMN_WIDTH) << "Samples";
	out() << std::right << std::setw(NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH) << "Iter/Sample";
	out() << std::right << std::setw(TOTAL_TIME_COLUMN_WIDTH) << "Time (s)";
	out() << std::right << std::setw(MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH) << "msec/Sample";
	out() << std::right << std::setw(MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH) << "+/-";
	out() << std::right << std::setw(NSEC_PER_ITEM_MEAN_COLUMN_WIDTH) << "nsec/Item";
	out() << std::right << std::setw(ITEMS_PER_SEC_COLUMN_WIDTH) << "MItems/sec";
	out() << "\n";
	out() << std::string(TOTAL_WIDTH, '-');
	out() << std::endl;
}

} // namespace luanics::benchmarking
