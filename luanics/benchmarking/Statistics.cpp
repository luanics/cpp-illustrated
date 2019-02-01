#include "luanics/benchmarking/Statistics.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace luanics {
namespace benchmarking {

Statistics::Statistics() :
	_count{0},
	_min{std::numeric_limits<double>::max()},
	_max{std::numeric_limits<double>::lowest()},
	_mean{0.0},
	_m2{0.0},
	_total{0.0}
{}

void Statistics::record(double const observation) {
	++_count;
	_total += observation;
	_min = std::min(_min, observation);
	_max = std::max(_max, observation);
	double const delta = observation - _mean;
	_mean += delta / _count;
	_m2 += delta * (observation - _mean);
}

std::size_t Statistics::count() const {
	return _count;
}

double Statistics::min() const {
	return _count < 1 ? nan : _min;
}

double Statistics::max() const {
	return _count < 1 ? nan : _max;
}

double Statistics::mean() const {
	return _count < 1 ? nan : _mean;
}

double Statistics::stdDev() const {
	return _count < 1 ? nan : (_count < 2 ? 0 : std::sqrt(_m2 / static_cast<double>(_count - 1)));
}

double Statistics::total() const {
	return _total < 1 ? nan : _total;
}

} // namespace benchmarking
} // namespace luanics
