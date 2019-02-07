#pragma once

#include "luanics/benchmarking/Result.hpp"
#include "luanics/benchmarking/Reporter.hpp"
#include "luanics/logging/Contract.hpp"
#include "luanics/statistics/Online.hpp"
#include "luanics/utility/Timer.hpp"

#include <vector>

namespace luanics::benchmarking {

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
	) :
		_reporter{reporter},
		_timer{},
		_numIterationsPerSample{numIterationsPerSample},
		_numRecordedSamples{numRecordedSamples},
		_numUnrecordedSamples{numUnrecordedSamples},
		_params{params.begin(), params.end()},
		_param{0},
		_numIterationsInThisSample{0},
		_numSamples{0},
		_currentResult{}
	{
		EXPECTS(numIterationsPerSample >= 1);
		EXPECTS(numRecordedSamples >= 1);
	}

	ParamType param() const {
		EXPECTS(not _params.empty());
		return _param;
	}
	unsigned totalNumIterations() const {
		return _numSamples * _numIterationsPerSample;
	}

	template <typename BenchmarkT>
	void run(std::string const & name, BenchmarkT benchmark) {
		if (_params.empty()) {
			run(name, benchmark, false);
			run(name, benchmark, true);
		}
		else {
			for (unsigned const param: _params) {
				std::string label = name + ":" + std::to_string(param);
				_param = param;
				run(label, benchmark, false);
				run(label, benchmark, true);
			}
		}
	}

	bool isRunning() {
		bool const isSampleFinished = _numIterationsInThisSample == _numIterationsPerSample;
		if (isSampleFinished) {
			auto elapsed = _timer.elapsed();
			double const nanosecondsElapsed = std::chrono::nanoseconds(elapsed).count();
			_numIterationsInThisSample = 0;
			++_numSamples;
			_currentResult._stats.record(nanosecondsElapsed);
		}
		bool const isBenchmarkFinished = _numSamples == _numSamplesTarget;
		if (isBenchmarkFinished) {
			return false;
		}
		bool const isSampleStarting = _numIterationsInThisSample == 0;
		if (isSampleStarting) {
			_timer.start();
		}
		++_numIterationsInThisSample;
		return true;
	}

	void setNumItemsProcessed(std::size_t const count) {
		_currentResult._numItemsProcessed = count;
	}
	void setNumBytesProcessed(std::size_t const count) {
		_currentResult._numBytesProcessed = count;
	}
	void setInfo(std::string info) {
		_currentResult._info = std::move(info);
	}

private:
	template <typename BenchmarkT>
	void run(std::string label, BenchmarkT benchmark, bool const isRecorded) {
		_currentResult = Result{std::move(label), _numIterationsPerSample};
		_numIterationsInThisSample = 0;
		_numSamplesTarget = isRecorded ? _numRecordedSamples : _numUnrecordedSamples;
		_numSamples = 0;
		benchmark(*this);
		if (isRecorded) {
			_reporter->report(_currentResult);
		}
	}

	Reporter * _reporter;
	utility::Timer<> _timer;
	unsigned _numIterationsPerSample;
	unsigned _numRecordedSamples;
	unsigned _numUnrecordedSamples;
	std::vector<ParamType> _params;
	ParamType _param;
	unsigned _numIterationsInThisSample;
	unsigned _numSamplesTarget;
	unsigned _numSamples;
	Result _currentResult;
}; // class Benchmarker

} // namespace luanics::benchmarking
