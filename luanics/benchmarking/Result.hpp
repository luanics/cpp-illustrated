#pragma once

#include "luanics/logging/Contract.hpp"
#include "luanics/statistics/Online.hpp"

#include <cmath>
#include <string>

namespace luanics::benchmarking {

struct Result {
	Result() = default;
	Result(
		std::string label,
		std::size_t const numIterationsPerSample
	) :
		_label{std::move(label)},
		_numIterationsPerSample{numIterationsPerSample},
		_numItemsProcessed{0},
		_numBytesProcessed{0},
		_stats{} {}

	std::size_t numSamples() const {return _stats.count();}
	std::size_t numIterationsPerSample() const {return _numIterationsPerSample;}
	std::size_t totalNumIterations() const {return _numIterationsPerSample * numSamples();}
	double totalTimeInNsec() const {return _stats.total();}
	double totalTimeInSec() const {return totalTimeInNsec() * 1e-9;}
	double msecPerSampleMean() const {return _stats.mean() * 1e-6;}
	double msecPerSampleStdDev() const {return _stats.stdDev() * 1e-6;}

	bool hasNumItemsProcessed() const {return _numItemsProcessed > 0;}
	double itemsPerSample() const {return _numItemsProcessed / numSamples();}
	std::size_t numItemsProcessed() const {
		ENSURES(hasNumItemsProcessed());
		return _numItemsProcessed;
	}
	bool hasInfo() const {return not _info.empty();}
	std::string const & info() const {return _info;}

//	X_Sample = X_Item1 + X_Item2 + ... + X_ItemN
//	E(X_Sample) = N * E(X_Item)
//  Var(X_Sample) = N * Var(X_Item)
//  Var(X_Item) = Var(X_Sample) / N
//  StdDev(X_Sample) = sqrt(N) * StdDev(X_Item)
//  StdDev(X_Item) = StdDev(X_Sample) / sqrt(N)
	double nsecPerItemMean() const {return msecPerSampleMean() * 1e6 / itemsPerSample();}
	/// sigma_n = sqrt(n) * sigma_1
	double nsecPerItemStdDev() const {return msecPerSampleStdDev() * 1e6 / std::sqrt(itemsPerSample());}
	double itemsPerSec() const {return _numItemsProcessed / totalTimeInSec();}

	double bytesPerSec() const {return _numBytesProcessed / totalTimeInSec();}

	std::string _label;
	std::size_t _numIterationsPerSample;
	std::size_t _numItemsProcessed;
	std::size_t _numBytesProcessed;
	statistics::Online _stats;
	std::string _info;
}; // class Result

} // namespace luanics::benchmarking
