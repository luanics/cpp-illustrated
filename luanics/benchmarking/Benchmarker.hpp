#pragma once

#include "luanics/statistics/Online.hpp"
#include "luanics/utility/Timer.hpp"

#include <vector>

namespace luanics::benchmarking {

class Reporter;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Benchmarker
///
/// @brief Benchmark runner.
///
/// Samples taken in two stages:
/// * first, runs numWarmupSamplesTarget number of samples, unrecorded
/// * second, runs numSamplesTarget number of samples, recorded
///
/// Benchmarker is constructed with a Reporter so that it can give incremental
///   feedback about the benchmark results.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Benchmarker {
public:
	using ParamType = std::size_t;

	/// @pre numIterationsPerSample >= 1
	/// @pre numRecordedSamples >= 1
	Benchmarker(
		Reporter * reporter,
		unsigned const numRecordedSamples,
		unsigned const numIterationsPerSample,
		std::initializer_list<ParamType> params = {},
		unsigned const numUnrecordedSamples = 0
	);

	unsigned totalNumIterations() const;

	template <typename BenchmarkT>
	void run(std::string const & name, BenchmarkT benchmark);

	////////////////////////////////////////////////////////
	/// @name Benchmark interface
	/// Can be called by the benchmark function from within run()
	////////////////////////////////////////////////////////
	//@{
	ParamType currentParam() const;
	bool isRunning(); ///< Must call after every benchmark sample
	void setNumItemsProcessed(std::size_t const count);
	//@}

private:
	template <typename BenchmarkT>
	void run(std::string label, BenchmarkT benchmark, bool const isRecorded);

	Reporter * _reporter;
	utility::Timer<> _timer;
	unsigned _numIterationsPerSample;
	unsigned _numRecordedSamples;
	unsigned _numUnrecordedSamples;
	std::vector<ParamType> _params;
	ParamType _currentParam;
	unsigned _numIterationsInThisSample;
	unsigned _numSamplesTarget;
	unsigned _numSamples;
	using ObservationType = std::chrono::nanoseconds::rep;
	using StatsType = statistics::Online<ObservationType>;
	StatsType _currentStats;
	std::size_t _currentNumItemsProcessed;
}; // class Benchmarker

} // namespace luanics::benchmarking

#include "luanics/benchmarking/Benchmarker.ipp"
