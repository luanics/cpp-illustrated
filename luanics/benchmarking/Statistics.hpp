#pragma once

#include <cstdint>
#include <limits>

namespace luanics {
namespace benchmarking {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Statistics
///
/// @brief Gather basic descriptive statistics using *online* algorithm.
///
/// @see https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Statistics {
public:
	static constexpr double nan = std::numeric_limits<double>::quiet_NaN();

	Statistics();

	void record(double const observation);

	std::size_t count() const; ///< @return num observations recorded
	double min() const;    ///< @returns nan if count() == 0
	double max() const;    ///< @returns nan if count() == 0
	double mean() const;   ///< @returns nan if count() == 0
	double stdDev() const; ///< @returns nan if count() == 0
	double total() const;  ///< @returns nan if count() == 0

private:
	std::size_t _count;
	double _min;
	double _max;
	double _mean;
	double _m2;
	double _total;
};
// class Statistics

} // namespace benchmarking
} // namespace luanics
