#pragma once

#include "luanics/logging/Contract.hpp"
#include "luanics/statistics/Online.hpp"

#include <chrono>
#include <cmath>
#include <string>

namespace luanics::benchmarking {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Result
///
/// @brief Statistics gathered about a benchmark.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
struct Result {
	Result() = default;
	Result(
		std::string label,
		std::size_t const numSamples,
		std::size_t const numIterationsPerSample,
		double const nsecTotal,
		double const nsecPerSampleMean,
		double const nsecPerSampleStdDev,
		std::size_t const numItemsProcessed = {}
	) :
		_label{std::move(label)},
		_numSamples{numSamples},
		_numIterationsPerSample{numIterationsPerSample},
		_nsecTotal{nsecTotal},
		_nsecPerSampleMean{nsecPerSampleMean},
		_nsecPerSampleStdDev{nsecPerSampleStdDev},
		_numItemsProcessed{numItemsProcessed}
	{}

	std::string const & label() const {return _label;}
	std::size_t numSamples() const {return _numSamples;}
	std::size_t numIterationsPerSample() const {return _numIterationsPerSample;}
	std::size_t totalNumIterations() const {return _numIterationsPerSample * numSamples();}
	double nsecTotal() const {return _nsecTotal;}
	double nsecPerSampleMean() const {return _nsecPerSampleMean;}
	double nsecPerSampleStdDev() const {return _nsecPerSampleStdDev;}

	bool hasNumItemsProcessed() const {return _numItemsProcessed > 0;}
	double itemsPerSample() const {return numItemsProcessed() / numSamples();}
	std::size_t numItemsProcessed() const {
		ENSURES(hasNumItemsProcessed());
		return _numItemsProcessed;
	}

private:
	std::string _label;
	std::size_t _numSamples;
	std::size_t _numIterationsPerSample;
	double _nsecTotal;
	double _nsecPerSampleMean;
	double _nsecPerSampleStdDev;
	std::size_t _numItemsProcessed;
}; // class Result

} // namespace luanics::benchmarking
