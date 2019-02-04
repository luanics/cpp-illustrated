#pragma once

#include "luanics/benchmark/Result.hpp"
#include "luanics/benchmark/Reporter.hpp"
#include "luanics/logging/Contract.hpp"
#include "luanics/performance/Statistics.hpp"
#include "luanics/time/Timer.hpp"

#include <vector>

namespace luanics {
namespace benchmark {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Benchmark
///
/// @brief Benchmark runner.
///
/// First runs numWarmupSamplesTarget number of samples, unrecorded
/// Second runs numSamplesTarget number of samples, recorded
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Benchmark {
public:
	using ParamType = std::size_t;

	/// @pre numIterationsPerSample >= 1
	/// @pre numRecordedSamples >= 1
	Benchmark(
		Reporter * reporter,
		std::string name,
		unsigned const numRecordedSamples,
		unsigned const numIterationsPerSample,
		std::initializer_list<ParamType> params = {},
		unsigned const numUnrecordedSamples = 0
	) :
		_reporter{reporter},
		_timer{},
		_name{std::move(name)},
		_numIterationsPerSample{numIterationsPerSample},
		_numRecordedSamples{numRecordedSamples},
		_numUnrecordedSamples{numUnrecordedSamples},
		_params{params.begin(), params.end()},
		_param{0},
		_numIterationsInThisSample{0},
		_numSamples{0},
		_currentResult{}
	{
		PRECONDITION(numIterationsPerSample >= 1);
		PRECONDITION(numRecordedSamples >= 1);
	}

	ParamType param() const {
		PRECONDITION(not _params.empty());
		return _param;
	}
	unsigned totalNumIterations() const {
		return _numSamples * _numIterationsPerSample;
	}

	template <typename SubjectT>
	void run(SubjectT subject) {
		if (_params.empty()) {
			run(_name, subject, false);
			run(_name, subject, true);
		}
		else {
			for (unsigned const param: _params) {
				std::string label = _name + ":" + std::to_string(param);
				_param = param;
				run(label, subject, false);
				run(label, subject, true);
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
	template <typename SubjectT>
	void run(std::string label, SubjectT subject, bool const isRecorded) {
		_currentResult = Result{std::move(label), _numIterationsPerSample};
		_numIterationsInThisSample = 0;
		_numSamplesTarget = isRecorded ? _numRecordedSamples : _numUnrecordedSamples;
		_numSamples = 0;
		subject(*this);
		if (isRecorded) {
			_reporter->report(_currentResult);
		}
	}

	Reporter * _reporter;
	Timer<> _timer;
	std::string _name;
	unsigned _numIterationsPerSample;
	unsigned _numRecordedSamples;
	unsigned _numUnrecordedSamples;
	std::vector<ParamType> _params;
	ParamType _param;
	unsigned _numIterationsInThisSample;
	unsigned _numSamplesTarget;
	unsigned _numSamples;
	Result _currentResult;
};
// class Benchmark

} // namespace benchmark
} // namespace luanics
