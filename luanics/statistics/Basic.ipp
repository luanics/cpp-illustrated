#include "luanics/statistics/Basic.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>

namespace luanics::statistics {

template <typename ObservationT>
Basic<ObservationT>::Basic() :
	_count{},
	_total{},
	_min{std::numeric_limits<ObservationType>::max()},
	_max{std::numeric_limits<ObservationType>::lowest()}
{}

template <typename ObservationT>
void Basic<ObservationT>::record(ObservationType observation) {
	++_count;
	_total += observation;
	_min = std::min(_min, observation);
	_max = std::max(_max, observation);
}

template <typename ObservationT>
std::size_t Basic<ObservationT>::count() const {return _count;}

template <typename ObservationT>
ObservationT Basic<ObservationT>::total() const {return _total;}

template <typename ObservationT>
double Basic<ObservationT>::mean() const {
	return static_cast<double>(total()) / static_cast<double>(count());
}

template <typename ObservationT>
ObservationT Basic<ObservationT>::min() const {return _min;}

template <typename ObservationT>
ObservationT Basic<ObservationT>::max() const {return _max;}

} // namespace luanics::statistics
