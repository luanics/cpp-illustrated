#pragma once

#include "luanics/benchmark/Reporter.hpp"
#include "luanics/benchmark/Result.hpp"
#include "luanics/performance/Statistics.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include "../utility/Colors.hpp"

namespace luanics {
namespace benchmark {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class TableReporter
///
/// @brief Displays Benchmark Results in a table format
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class TableReporter : public Reporter {
public:
	static constexpr unsigned LABEL_COLUMN_WIDTH = 20;
	static constexpr unsigned NUM_SAMPLES_COLUMN_WIDTH = 12;
	static constexpr unsigned NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH = 12;
	static constexpr unsigned TOTAL_TIME_COLUMN_WIDTH = 12;
	static constexpr unsigned MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH = 12;
	static constexpr unsigned MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH = 10;
	static constexpr unsigned NSEC_PER_ITEM_MEAN_COLUMN_WIDTH = 12;
	static constexpr unsigned ITEMS_PER_SAMPLE_COLUMN_WIDTH = 12;
	static constexpr unsigned ITEMS_PER_SEC_COLUMN_WIDTH = 12;
	static constexpr unsigned BYTES_PER_SEC_COLUMN_WIDTH = 12;
	static constexpr unsigned INFO_COLUMN_WIDTH = 12;
	static constexpr unsigned TOTAL_WIDTH =
			LABEL_COLUMN_WIDTH
			+ NUM_SAMPLES_COLUMN_WIDTH
			+ NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH
			+ TOTAL_TIME_COLUMN_WIDTH
			+ MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH
			+ MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH
			+ NSEC_PER_ITEM_MEAN_COLUMN_WIDTH
			+ ITEMS_PER_SEC_COLUMN_WIDTH
			+ BYTES_PER_SEC_COLUMN_WIDTH
			+ INFO_COLUMN_WIDTH;


	TableReporter(std::ostream * out) : _out{out} {
		printHeader();
	}

	void report(Result const & result) {
		out() << color::green << std::left << std::setw(LABEL_COLUMN_WIDTH) << result._label;
		out() << color::cyan << std::right << std::setw(NUM_SAMPLES_COLUMN_WIDTH) << std::fixed << std::setprecision(0) << result.numSamples();
		out() << color::cyan << std::right << std::setw(NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH) << std::fixed << std::setprecision(0) << result.numIterationsPerSample();
		out() << color::yellow << std::right << std::setw(TOTAL_TIME_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << result.totalTimeInSec();
		out() << color::white << std::right << std::setw(MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << result.msecPerSampleMean();
		out() << color::darkGray << std::right << std::setw(MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH) << std::fixed << std::setprecision(3) << result.msecPerSampleStdDev();
		if (result.hasNumItemsProcessed()) {
			out() << color::white << std::right << std::setw(NSEC_PER_ITEM_MEAN_COLUMN_WIDTH) << std::fixed << std::setprecision(1) << result.nsecPerItemMean();
			double const megaItemsPerSecond = result.itemsPerSec() * 1.0e-6;
			out() << color::white << std::right << std::setw(ITEMS_PER_SEC_COLUMN_WIDTH) << std::fixed << std::setprecision(2) << megaItemsPerSecond;
		}
		else {
			out() << std::string(ITEMS_PER_SEC_COLUMN_WIDTH, ' ');
		}
		double const megaBytesPerSecond = result.bytesPerSec() * 1.0e-6;
		if (megaBytesPerSecond > 0.0) {
			out() << color::white << std::right << std::setw(BYTES_PER_SEC_COLUMN_WIDTH) << std::fixed << std::setprecision(2) << megaBytesPerSecond;
		}
		else {
			out() << std::string(BYTES_PER_SEC_COLUMN_WIDTH, ' ');
		}
		if (result.hasInfo()) {
			out() << color::white << std::right << std::setw(INFO_COLUMN_WIDTH) << result.info();
		}
		out() << color::reset << "\n";
		out().flush();
	}

private:
	std::ostream & out() {return *_out;}

	void printHeader() {
		out() << std::left << std::setw(LABEL_COLUMN_WIDTH) << "Benchmark";
		out() << std::right << std::setw(NUM_SAMPLES_COLUMN_WIDTH) << "Samples";
		out() << std::right << std::setw(NUM_ITERATIONS_PER_SAMPLE_COLUMN_WIDTH) << "Iter/Sample";
		out() << std::right << std::setw(TOTAL_TIME_COLUMN_WIDTH) << "Time (s)";
		out() << std::right << std::setw(MSEC_PER_SAMPLE_MEAN_COLUMN_WIDTH) << "msec/Sample";
		out() << std::right << std::setw(MSEC_PER_SAMPLE_STDDEV_COLUMN_WIDTH) << "+/-";
		out() << std::right << std::setw(NSEC_PER_ITEM_MEAN_COLUMN_WIDTH) << "nsec/Item";
		out() << std::right << std::setw(ITEMS_PER_SEC_COLUMN_WIDTH) << "MItems/sec";
		out() << std::right << std::setw(BYTES_PER_SEC_COLUMN_WIDTH) << "MBytes/sec";
		out() << std::right << std::setw(INFO_COLUMN_WIDTH) << "Info";
		out() << "\n";
		out() << std::string(TOTAL_WIDTH, '-');
		out() << std::endl;
	}

	std::ostream * _out;

}; // class TableReporter

} // namespace benchmark
} // namespace luanics
