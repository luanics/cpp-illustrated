#include "luanics/logging/Contract.hpp"
#include "luanics/statistics/Online.hpp"

#include <cmath>

namespace luanics {
namespace statistics {

template <typename ObservationT>
Online<ObservationT>::Online() :
	_count{},
	_total{},
	_min{},
	_max{},
	_mean{},
	_m2{}
{}

template <typename ObservationT>
void Online<ObservationT>::record(ObservationType const observation) {
	++_count;
	if (_count == 1) {
		_min = observation;
		_max = observation;
	}
	else {
		_min = std::min(_min, observation);
		_max = std::max(_max, observation);
	}
	double const delta = observation - _mean;
	_mean += delta / _count;
	_m2 += delta * (observation - _mean);
}

template <typename ObservationT>
std::size_t Online<ObservationT>::count() const {
	return _count;
}

template <typename ObservationT>
ObservationT Online<ObservationT>::min() const {
	ENSURES(count() > 0);
	return _min;
}

template <typename ObservationT>
ObservationT Online<ObservationT>::max() const {
	ENSURES(count() > 0);
	return _max;
}

template <typename ObservationT>
double Online<ObservationT>::mean() const {
	ENSURES(count() > 0);
	return _mean;
}

template <typename ObservationT>
double Online<ObservationT>::stdDev() const {
	ENSURES(count() > 0);
	if (_count == 1) return 0.0;
	else return std::sqrt(_m2 / static_cast<double>(_count - 1));
}

} // namespace statistics
} // namespace luanics
