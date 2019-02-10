#include "luanics/benchmarking/Benchmarker.hpp"

#include "luanics/benchmarking/Reporter.hpp"
#include "luanics/benchmarking/Result.hpp"
#include "luanics/logging/Contract.hpp"

namespace luanics::benchmarking {

Benchmarker::Benchmarker(
	Reporter * reporter,
	unsigned const numRecordedSamples,
	unsigned const numIterationsPerSample,
	std::initializer_list<ParamType> params,
	unsigned const numUnrecordedSamples
) :
	_reporter{reporter},
	_timer{},
	_numIterationsPerSample{numIterationsPerSample},
	_numRecordedSamples{numRecordedSamples},
	_numUnrecordedSamples{numUnrecordedSamples},
	_params{params.begin(), params.end()},
	_currentParam{},
	_numIterationsInThisSample{},
	_numSamplesTarget{},
	_numSamples{},
	_currentStats{},
	_currentNumItemsProcessed{}
{
	EXPECTS(numIterationsPerSample >= 1);
	EXPECTS(numRecordedSamples >= 1);
}

inline Benchmarker::ParamType Benchmarker::currentParam() const {
	EXPECTS(not _params.empty());
	return _currentParam;
}

inline unsigned Benchmarker::totalNumIterations() const {
	return _numSamples * _numIterationsPerSample;
}

template <typename BenchmarkT>
void Benchmarker::run(std::string const & name, BenchmarkT benchmark) {
	if (_params.empty()) {
		run(name, benchmark, false);
		run(name, benchmark, true);
	}
	else {
		for (unsigned const param: _params) {
			std::string label = name + ":" + std::to_string(param);
			_currentParam = param;
			run(label, benchmark, false);
			run(label, benchmark, true);
		}
	}
}

inline bool Benchmarker::isRunning() {
	bool const isSampleFinished = _numIterationsInThisSample == _numIterationsPerSample;
	if (isSampleFinished) {
		auto elapsed = _timer.elapsed();
		double const nanosecondsElapsed = std::chrono::nanoseconds(elapsed).count();
		_numIterationsInThisSample = 0;
		++_numSamples;
		_currentStats.record(nanosecondsElapsed);
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

inline void Benchmarker::setNumItemsProcessed(std::size_t const count) {
	_currentNumItemsProcessed = count;
}

template <typename BenchmarkT>
void Benchmarker::run(std::string label, BenchmarkT benchmark, bool const isRecorded) {
	_numIterationsInThisSample = 0;
	_numSamplesTarget = isRecorded ? _numRecordedSamples : _numUnrecordedSamples;
	_numSamples = 0;
	_currentStats = StatsType{};
	_currentNumItemsProcessed = 0;
	benchmark(*this);
	if (isRecorded) {
		_reporter->report(Result{
			std::move(label),
			_currentStats.count(),
			_numIterationsPerSample,
			static_cast<double>(_currentStats.total()),
			_currentStats.mean(),
			_currentStats.stdDev(),
			_currentNumItemsProcessed
		});
	}
}

} // namespace luanics::benchmarking
